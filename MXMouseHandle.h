// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include <queue>
#include <bitset>
#include <optional>

class MXMouseHandle;
struct MXMouseHandleEvent
{
public:
	enum class EMXMouseHandleEventType
	{
		LMBPress,
		LMBRelease,
		RMBPress,
		RMBRelease,
		Move,
		EnterWindow,
		LeaveWindow,
		WheelUp,
		WheelDown,
		Invalid
	};

public:
	MXMouseHandleEvent();
	MXMouseHandleEvent( EMXMouseHandleEventType const EventType, bool const LMBPressed, bool const RMBPressed, int const PosX, int const PosY );
	MXMouseHandleEvent( EMXMouseHandleEventType const EventType, MXMouseHandle const& Parent );

	EMXMouseHandleEventType const& GetEventType() const;
	bool IsLMBPressed() const;
	bool IsRMBPressed() const;
	std::pair< int, int > GetPosition() const;
	int GetPosX() const;
	int GetPosY() const;
	bool IsValid() const;

private:
	EMXMouseHandleEventType EventType = EMXMouseHandleEventType::Invalid;
	bool LMBPressed = false;
	bool RMBPressed = false;
	int PosX = 0;
	int PosY = 0;
};

class MXMouseHandle
{
public:
	MXMouseHandle();

	bool IsLMBPressed() const;
	bool IsRMBPressed() const;
	bool IsMouseInWindow() const;
	std::pair< int, int > GetPosition() const;
	int GetPosX() const;
	int GetPosY() const;

	std::optional< MXMouseHandleEvent > Read();

	bool IsEmpty() const;

	void Clear();

	void OnMouseMove( int const PosX, int const PosY );
	void OnLMBPressed( int const PosX, int const PosY );
	void OnLMBReleased( int const PosX, int const PosY );
	void OnRMBPressed( int const PosX, int const PosY );
	void OnRMBReleased( int const PosX, int const PosY );
	void OnWheelUp( int const PosX, int const PosY );
	void OnWheelDown( int const PosX, int const PosY );
	void OnMouseEnterWindow();
	void OnMouseLeaveWindow();

	void TrimBuffer();

private:
	static constexpr unsigned int BufferSize = 16u;
	bool LMBPressed = false;
	bool RMBPressed = false;
	bool MouseInWindow = false;
	int PositionX = 0;
	int PositionY = 0;
	std::queue< MXMouseHandleEvent > EventBuffer;
};
