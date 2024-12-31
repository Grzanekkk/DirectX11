// Copyright (c) 2024, Made by Jan Puto :>
#include "Input/MXMouseHandle.h"

MXMouseHandleEvent::MXMouseHandleEvent()
	: EventType{ EMXMouseHandleEventType::Invalid }
	, LMBPressed{ false }
	, RMBPressed{ false }
	, PosX{ 0 }
	, PosY{ 0 }
{
}

MXMouseHandleEvent::MXMouseHandleEvent( EMXMouseHandleEventType const EventType, bool const LMBPressed, bool const RMBPressed, int const PosX, int const PosY )
	: EventType{ EventType }
	, LMBPressed{ LMBPressed }
	, RMBPressed{ RMBPressed }
	, PosX{ PosX }
	, PosY{ PosY }
{
}

MXMouseHandleEvent::MXMouseHandleEvent( EMXMouseHandleEventType const EventType, MXMouseHandle const& Parent )
	: EventType{ EventType }
	, LMBPressed{ Parent.IsLMBPressed() }
	, RMBPressed{ Parent.IsRMBPressed() }
	, PosX{ Parent.GetPosX() }
	, PosY{ Parent.GetPosY() }
{
}

MXMouseHandleEvent::EMXMouseHandleEventType const& MXMouseHandleEvent::GetEventType() const
{
	return EventType;
}

bool MXMouseHandleEvent::IsLMBPressed() const
{
	return LMBPressed;
}

bool MXMouseHandleEvent::IsRMBPressed() const
{
	return RMBPressed;
}

std::pair< int, int > MXMouseHandleEvent::GetPosition() const
{
	return std::pair< int, int >( PosX, PosY );
}

int MXMouseHandleEvent::GetPosX() const
{
	return PosX;
}

int MXMouseHandleEvent::GetPosY() const
{
	return PosY;
}

bool MXMouseHandleEvent::IsValid() const
{
	return EventType != EMXMouseHandleEventType::Invalid;
}

MXMouseHandle::MXMouseHandle()
	: LMBPressed{ false }
	, RMBPressed{ false }
	, PositionX{ 0 }
	, PositionY{ 0 }
{
}

bool MXMouseHandle::IsLMBPressed() const
{
	return LMBPressed;
}

bool MXMouseHandle::IsRMBPressed() const
{
	return RMBPressed;
}

bool MXMouseHandle::IsMouseInWindow() const
{
	return MouseInWindow;
}

std::pair< int, int > MXMouseHandle::GetPosition() const
{
	return std::pair< int, int >( PositionX, PositionY );
}

int MXMouseHandle::GetPosX() const
{
	return PositionX;
}

int MXMouseHandle::GetPosY() const
{
	return PositionY;
}

std::optional< MXMouseHandleEvent > MXMouseHandle::Read()
{
	if( EventBuffer.size() > 0u )
	{
		MXMouseHandleEvent const Event = EventBuffer.front();
		EventBuffer.pop();
		return Event;
	}

	return {};
}

bool MXMouseHandle::IsEmpty() const
{
	return EventBuffer.empty();
}

void MXMouseHandle::Clear()
{
	EventBuffer = std::queue< MXMouseHandleEvent >();
}

void MXMouseHandle::OnMouseMove( int const PosX, int const PosY )
{
	PositionX = PosX;
	PositionY = PosY;

	EventBuffer.push( MXMouseHandleEvent( MXMouseHandleEvent::EMXMouseHandleEventType::Move, *this ) );
	TrimBuffer();
}

void MXMouseHandle::OnLMBPressed( int const PosX, int const PosY )
{
	LMBPressed = true;

	EventBuffer.push( MXMouseHandleEvent( MXMouseHandleEvent::EMXMouseHandleEventType::LMBPress, *this ) );
	TrimBuffer();
}

void MXMouseHandle::OnLMBReleased( int const PosX, int const PosY )
{
	LMBPressed = false;

	EventBuffer.push( MXMouseHandleEvent( MXMouseHandleEvent::EMXMouseHandleEventType::LMBRelease, *this ) );
	TrimBuffer();
}

void MXMouseHandle::OnRMBPressed( int const PosX, int const PosY )
{
	RMBPressed = true;

	EventBuffer.push( MXMouseHandleEvent( MXMouseHandleEvent::EMXMouseHandleEventType::RMBPress, *this ) );
	TrimBuffer();
}

void MXMouseHandle::OnRMBReleased( int const PosX, int const PosY )
{
	RMBPressed = false;

	EventBuffer.push( MXMouseHandleEvent( MXMouseHandleEvent::EMXMouseHandleEventType::RMBRelease, *this ) );
	TrimBuffer();
}

void MXMouseHandle::OnWheelUp( int const PosX, int const PosY )
{
	EventBuffer.push( MXMouseHandleEvent( MXMouseHandleEvent::EMXMouseHandleEventType::WheelUp, *this ) );
	TrimBuffer();
}

void MXMouseHandle::OnWheelDown( int const PosX, int const PosY )
{
	EventBuffer.push( MXMouseHandleEvent( MXMouseHandleEvent::EMXMouseHandleEventType::WheelDown, *this ) );
	TrimBuffer();
}

void MXMouseHandle::OnMouseEnterWindow()
{
	MouseInWindow = true;

	EventBuffer.push( MXMouseHandleEvent( MXMouseHandleEvent::EMXMouseHandleEventType::EnterWindow, *this ) );
	TrimBuffer();
}

void MXMouseHandle::OnMouseLeaveWindow()
{
	MouseInWindow = false;

	EventBuffer.push( MXMouseHandleEvent( MXMouseHandleEvent::EMXMouseHandleEventType::LeaveWindow, *this ) );
	TrimBuffer();
}

void MXMouseHandle::TrimBuffer()
{
	while( EventBuffer.size() > BufferSize )
	{
		EventBuffer.pop();
	}
}