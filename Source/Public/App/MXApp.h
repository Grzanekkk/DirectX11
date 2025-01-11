// Copyright (c) 2024, Made by Jan Puto :>
#pragma once

#include "MXWindow.h"
#include "Graphics/MXGraphicsTypes.h"

class MXApp
{
public:
	MXApp();

public:
	int StartApp();
	void Tick();

private:
	int WindowHeight = 600;
	int WindowWidth = 800;
	MXWindow WindowHandle;
	int TempTickCounter = 0;
	FColor BackGroudColor = FColor( 0.f, 0.f, 1.f );
	float CurrentRotation = 0.f;
	float RotationSpeed = 0.01;
};