// Copyright (c) 2024, Made by Jan Puto :>

#include "App/MXApp.h"
#include "Windows/MXWindow.h"
#include "Graphics/MXGraphics.h"
#include <random>
#include <iostream>

MXApp::MXApp()
	: WindowHandle{ WindowWidth, WindowHeight, "TOYOTA" }
{
}

int MXApp::StartApp()
{
	while( true )
	{
		if( std::optional< int > const EscapeCode = WindowHandle.ProcessMessages() )
		{
			return EscapeCode.value();
		}

		Tick();
	}
}

void MXApp::Tick()
{
	TempTickCounter++;
	if( TempTickCounter > 30 )
	{
		TempTickCounter = 0;
		std::random_device rd;
		std::mt19937 gen( rd() );
		std::uniform_real_distribution< float > dis( 0.0, 1.0 );
		float const Red = dis( gen );
		float const Green = dis( gen );
		BackGroudColor = FColor( Red, Green, 1.f );
	}

	CurrentRotation += RotationSpeed;

	float const TriangleX = WindowHandle.GetMouseHandle().GetPosX() / ( float ) WindowWidth * 2.f - 1.f;
	float const TriangleY = -WindowHandle.GetMouseHandle().GetPosY() / ( float ) WindowHeight * 2.f + 1.f;

	std::cout << "X:" << TriangleX << std::endl;
	std::cout << "Y:" << TriangleY << std::endl;
	WindowHandle.GetGraphics().ClearBuffer( BackGroudColor.R, BackGroudColor.G, BackGroudColor.G );
	WindowHandle.GetGraphics().DrawTestTriangle( CurrentRotation, TriangleX, TriangleY );
	WindowHandle.GetGraphics().EndFrame();
}
