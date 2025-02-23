// Copyright (c) 2025, Made by Jan Puto :>
#include <chrono>

class MXClock
{
public:
	void StartClock();
	void Tick();
	float GetDeltaTime();

protected:
	std::chrono::time_point< std::chrono::high_resolution_clock > LastTime;
};