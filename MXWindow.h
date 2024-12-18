#pragma once

#include "MXWindowsSetup.h"

class MXWindow
{
public:
	MXWindow( int const Width, int const Height, char const* Name );
	~MXWindow();
	MXWindow( MXWindow const& ) = delete; // no need for copy constructor

protected:
	int Width = 0;
	int Height = 0;
	HWND hWnd;
};