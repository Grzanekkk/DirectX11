#include <Windows.h>
#include <string>
#include <iostream>

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
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	char const* const ClassName = "DirectXWindow";
	WNDCLASSEX WindowsClass = { 0 };
	WindowsClass.cbSize = sizeof( WindowsClass );
	WindowsClass.style = CS_OWNDC;
	WindowsClass.lpfnWndProc = DefaultWndProc;
	WindowsClass.cbClsExtra = 0;
	WindowsClass.cbWndExtra = 0;
	WindowsClass.hInstance = hInstance;
	WindowsClass.hIcon = nullptr;
	WindowsClass.hCursor = nullptr;
	WindowsClass.hbrBackground = nullptr;
	WindowsClass.lpszMenuName = nullptr;
	WindowsClass.lpszClassName = ClassName;
	WindowsClass.hIconSm = nullptr;

	RegisterClassEx( &WindowsClass );

	HWND WindowHandle = CreateWindowExA( 0, ClassName, "I love Win32 Api!!", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 200, 200, 640, 480, nullptr, nullptr, hInstance, nullptr );

	ShowWindow( WindowHandle, SW_SHOW );

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
		return Msg.wParam;
	}
}