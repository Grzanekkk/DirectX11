// Copyright (c) 2024, Made by Jan Puto :>
#pragma once

#include "MXWindow.h"
#include "Graphics/MXGraphicsTypes.h"
#include "Drawable/Shape/Box.h"
#include "Drawable/Shape/Pyramid.h"

class MXApp
{
public:
	MXApp();

public:
	int StartApp();
	void Tick();

private:
	int WindowHeight = 900;
	int WindowWidth = 1200;
	MXWindow WindowHandle;
	int TempTickCounter = 0;
	FColor BackGroudColor = FColor( 0.f, 0.f, 1.f );
	float CurrentRotation = 0.f;
	float RotationSpeed = 0.01;

	// #FIXME add parent class
	std::vector< std::unique_ptr< DBox > > Boxes;
	std::vector< std::unique_ptr< DPyramid > > Pyramids;
};