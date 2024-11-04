#include <Windows.h>
#include <string>
#include <iostream>

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	char const* const ClassName = "DirectXWindow";
	WNDCLASSEX WindowsClass = { 0 };
	WindowsClass.cbSize = sizeof( WindowsClass );
	WindowsClass.style = CS_OWNDC;
	WindowsClass.lpfnWndProc = DefWindowProc;
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

	while( true )
	{
	}

	return 0;
}