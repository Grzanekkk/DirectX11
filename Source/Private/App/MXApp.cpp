// Copyright (c) 2024, Made by Jan Puto :>

#include "App/MXApp.h"
#include "Windows/MXWindow.h"
#include "Graphics/MXGraphics.h"
#include <random>

MXApp::MXApp()
	: WindowHandle{ 800, 600, "TOYOTA" }
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
	std::random_device rd;
	std::mt19937 gen( rd() );
	std::uniform_real_distribution< float > dis( 0.0, 1.0 );
	float const Red = dis( gen );
	float const Green = dis( gen );

	WindowHandle.GetGraphics().ClearBuffer( Red, Green, 1.f );
	WindowHandle.GetGraphics().DrawTestTriangle();
	WindowHandle.GetGraphics().EndFrame();
}
