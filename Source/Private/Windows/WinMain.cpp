// Copyright (c) 2024, Made by Jan Puto :>

#include "Windows/MXWindow.h"
#include "App/MXApp.h"

//////////////////////////////////////////////////////////// ENTRY POINT ////////////////////////////////////////////////////////////
int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	try
	{
		MXApp App;
		App.StartApp();
	}
	catch( MXException const& e )
	{
		MessageBox( nullptr, e.what(), e.GetType(), MB_OK || MB_ICONEXCLAMATION );
	}
	catch( std::exception const& e )
	{
		MessageBox( nullptr, e.what(), "Standard Exception", MB_OK || MB_ICONEXCLAMATION );
	}
	catch( ... )
	{
		MessageBox( nullptr, "Unknown Exception", "Standard Exception", MB_OK || MB_ICONEXCLAMATION );
	}

	return 0;
}