// Copyright (c) 2024, Made by Jan Puto :>
#pragma once

#include "MXWindow.h"

class MXApp
{
public:
	MXApp();

public:
	int StartApp();
	void Tick();

	private:
	MXWindow WindowHandle;
};