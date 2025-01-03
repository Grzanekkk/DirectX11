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
	MXWindow WindowHandle;
	int TempTickCounter = 0;
	FColor BackGroudColor = FColor( 0.f, 0.f, 1.f );
};