// Copyright (c) 2025, Made by Jan Puto :>

#include "Clock/Clock.h"
#include <thread>

void MXClock::StartClock()
{
	LastTime = std::chrono::high_resolution_clock::now();
}

void MXClock::Tick()
{
	LastTime = std::chrono::high_resolution_clock::now();
}

float MXClock::GetDeltaTime()
{
	auto CurrentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration< float > DeltaTime = CurrentTime - LastTime;
	return DeltaTime.count();
}
