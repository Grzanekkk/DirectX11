// Copyright (c) 2024, Made by Jan Puto :>
#include "MXMouseHandle.h"

MXMouseHandleEvent::MXMouseHandleEvent()
	: EventType{ MXMouseHandleEventType::Invalid }
	, LMBPressed{ false }
	, RMBPressed{ false }
	, PosX{ 0 }
	, PosY{ 0 }
{
}

MXMouseHandleEvent::MXMouseHandleEvent( MXMouseHandleEventType const EventType, bool const LMBPressed, bool const RMBPressed, int const PosX, int const PosY )
	: EventType{ EventType }
	, LMBPressed{ LMBPressed }
	, RMBPressed{ RMBPressed }
	, PosX{ PosX }
	, PosY{ PosY }
{
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
	return EventType != MXMouseHandleEventType::Invalid;
}

MXMouseHandle::MXMouseHandle()
	: LMBPressed{ false }
	, RMBPressed{ false }
	, PosX{ 0 }
	, PosY{ 0 }
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

bool MXMouseHandle::GetIsInWindow() const
{
	return IsInWindow;
}

std::pair< int, int > MXMouseHandle::GetPosition() const
{
	return std::pair< int, int >( PosX, PosY );
}

int MXMouseHandle::GetPosX() const
{
	return PosX;
}

int MXMouseHandle::GetPosY() const
{
	return PosY;
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
	//EventBuffer.push( MXMouseHandleEvent( MXMouseHandleEvent::MXMouseHandleEventType::Press,) );
	TrimBuffer();
}

void MXMouseHandle::OnLMBPressed( int const PosX, int const PosY )
{
}

void MXMouseHandle::OnLMBReleased( int const PosX, int const PosY )
{
}

void MXMouseHandle::OnRMBPressed( int const PosX, int const PosY )
{
}

void MXMouseHandle::OnRMBReleased( int const PosX, int const PosY )
{
}

void MXMouseHandle::OnWheelUp( int const PosX, int const PosY )
{
}

void MXMouseHandle::OnWheelDown( int const PosX, int const PosY )
{
}

void MXMouseHandle::OnMouseEnterWindow( int const PosX, int const PosY )
{
}

void MXMouseHandle::OnMouseLeaveWindow( int const PosX, int const PosY )
{
}

void MXMouseHandle::TrimBuffer()
{
	while( EventBuffer.size() > BufferSize )
	{
		EventBuffer.pop();
	}
}