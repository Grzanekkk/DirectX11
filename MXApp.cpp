// Copyright (c) 2024, Made by Jan Puto :>

#include "MXApp.h"
#include "MXWindow.h"

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
}
