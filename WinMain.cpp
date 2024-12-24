// Copyright (c) 2024, Made by Jan Puto :>

#include "MXWindow.h"
#include <iostream>
#include <sstream>

bool HandleKeyDown( HWND hWnd, WPARAM KeyCode )
{
	if( KeyCode == 'F' )
	{
		SetWindowText( hWnd, "FFFFFFFFFFFFFF" );
	}

	return true;
}

bool HandleKeyUp( HWND hWnd, WPARAM KeyCode )
{
	if( KeyCode == 'F' )
	{
		SetWindowText( hWnd, "No more FFFFFFFFFFFFFF" );
	}

	return true;
}

bool HandleCharInput( HWND hWnd, WPARAM KeyCode )
{
	static std::string Title;
	Title.push_back( ( char ) KeyCode );
	SetWindowText( hWnd, Title.c_str() );

	return true;
}

bool HandleLMB( HWND hWnd, WPARAM wParam, LPARAM lParam )
{
	POINTS const pt = MAKEPOINTS( lParam );
	std::ostringstream title;
	title << "Click Click here: (" << pt.x << "," << pt.y << ")";

	SetWindowText( hWnd, title.str().c_str() );

	return true;
}

LRESULT CALLBACK DefaultWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
		case WM_CLOSE:
			PostQuitMessage( 2137 );
			break;
		case WM_KEYDOWN:
			HandleKeyDown( hWnd, wParam );
			break;
		case WM_KEYUP:
			HandleKeyUp( hWnd, wParam );
			break;
		case WM_CHAR:
			HandleCharInput( hWnd, wParam );
			break;
		case WM_LBUTTONDOWN:
			HandleLMB( hWnd, wParam, lParam );
			break;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	try
	{
		MXWindow MXWindowHandle( 800, 300, "TOYOTA" );

		// Message pump
		MSG Msg;
		BOOL gResult = -1;
		// gResult == 0 is posted when QUIT msg is send
		while( ( gResult = GetMessage( &Msg, nullptr, 0, 0 ) ) > 0 )
		{
			TranslateMessage( &Msg );
			DispatchMessage( &Msg );
		}

		if( gResult == -1 )
		{
			// Some Error
			return -1;
		}
		else
		{
			// Returns code send in PostQuitMessage()
			return ( int ) Msg.wParam;
		}
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
}