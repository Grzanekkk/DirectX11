// Copyright (c) 2024, Made by Jan Puto :>
#include "Input/MXKeyboardHandle.h"

MXKeyboardHandleEvent::MXKeyboardHandleEvent()
	: EventType{ MXKeyboardHandleEventType::Invalid }
	, KeyCode{ 0u }
{
}

MXKeyboardHandleEvent::MXKeyboardHandleEvent( MXKeyboardHandleEventType const EventType, unsigned char const KeyCode )
	: EventType{ EventType }
	, KeyCode{ KeyCode }
{
}

bool MXKeyboardHandleEvent::IsPressed() const
{
	return EventType == MXKeyboardHandleEventType::Press;
}

bool MXKeyboardHandleEvent::IsReleased() const
{
	return EventType == MXKeyboardHandleEventType::Release;
}

bool MXKeyboardHandleEvent::IsValid() const
{
	return EventType != MXKeyboardHandleEventType::Invalid;
}

unsigned int MXKeyboardHandleEvent::GetCode() const
{
	return KeyCode;
}

MXKeyboardHandle::MXKeyboardHandle()
{
}

bool MXKeyboardHandle::IsKeyPressed( unsigned char const KeyCode ) const
{
	return KeyStates[ KeyCode ];
}

std::optional< MXKeyboardHandleEvent > MXKeyboardHandle::ReadKey()
{
	if( KeyBuffer.size() > 0u )
	{
		MXKeyboardHandleEvent const Event = KeyBuffer.front();
		KeyBuffer.pop();
		return Event;
	}

	return {};
}

bool MXKeyboardHandle::IsKeyEmpty() const
{
	return KeyBuffer.empty();
}

void MXKeyboardHandle::ClearKey()
{
	KeyBuffer = std::queue< MXKeyboardHandleEvent >();
}

unsigned char MXKeyboardHandle::ReadChar()
{
	if( CharBuffer.size() > 0u )
	{
		unsigned int const Char = CharBuffer.front();
		CharBuffer.pop();
		return Char;
	}

	return 0;
}

bool MXKeyboardHandle::IsCharEmpty() const
{
	return CharBuffer.empty();
}

void MXKeyboardHandle::ClearChar()
{
	CharBuffer = std::queue< unsigned char >();
}

void MXKeyboardHandle::Clear()
{
	ClearKey();
	ClearChar();
}

void MXKeyboardHandle::EnableAutorepeat()
{
	AutorepeatEnabled = true;
}

void MXKeyboardHandle::DisableAutorepeat()
{
	AutorepeatEnabled = false;
}

bool MXKeyboardHandle::IsAutorepeatEnaled() const
{
	return AutorepeatEnabled;
}

void MXKeyboardHandle::OnKeyPressed( unsigned char const KeyCode )
{
	KeyStates[ KeyCode ] = true;
	KeyBuffer.push( MXKeyboardHandleEvent( MXKeyboardHandleEvent::MXKeyboardHandleEventType::Press, KeyCode ) );
	TrimBuffer( KeyBuffer );
}

void MXKeyboardHandle::OnKeyReleased( unsigned char const KeyCode )
{
	KeyStates[ KeyCode ] = false;
	KeyBuffer.push( MXKeyboardHandleEvent( MXKeyboardHandleEvent::MXKeyboardHandleEventType::Release, KeyCode ) );
	TrimBuffer( KeyBuffer );
}

void MXKeyboardHandle::OnChar( char const Character )
{
	CharBuffer.push( Character );
	TrimBuffer( CharBuffer );
}

void MXKeyboardHandle::ClearState()
{
	KeyStates.reset();
}

template< typename T >
inline void MXKeyboardHandle::TrimBuffer( std::queue< T >& Buffer )
{
	while( Buffer.size() > BufferSize )
	{
		Buffer.pop();
	}
}
