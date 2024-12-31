// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include <queue>
#include <bitset>
#include <optional>

struct MXKeyboardHandleEvent
{
public:
	enum class MXKeyboardHandleEventType
	{
		Press,
		Release,
		Invalid
	};

public:
	MXKeyboardHandleEvent();
	MXKeyboardHandleEvent( MXKeyboardHandleEventType const EventType, unsigned char const KeyCode );

	bool IsPressed() const;
	bool IsReleased() const;
	bool IsValid() const;
	unsigned int GetCode() const;

private:
	MXKeyboardHandleEventType EventType = MXKeyboardHandleEventType::Invalid;
	unsigned char KeyCode;
};

class MXKeyboardHandle
{
public:
	MXKeyboardHandle();

	bool IsKeyPressed( unsigned char const KeyCode ) const;
	std::optional< MXKeyboardHandleEvent > ReadKey();
	bool IsKeyEmpty() const;
	void ClearKey();

	unsigned char ReadChar();
	bool IsCharEmpty() const;
	void ClearChar();
	void Clear();

	void EnableAutorepeat();
	void DisableAutorepeat();
	bool IsAutorepeatEnaled() const;

	void OnKeyPressed( unsigned char const KeyCode );
	void OnKeyReleased( unsigned char const KeyCode );
	void OnChar( char const Character );
	void ClearState();

	template< typename T >
	static void TrimBuffer( std::queue< T >& Buffer );

private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int BufferSize = 16u;
	bool AutorepeatEnabled = false;
	std::bitset< nKeys > KeyStates;
	std::queue< MXKeyboardHandleEvent > KeyBuffer;
	std::queue< unsigned char > CharBuffer;
};
