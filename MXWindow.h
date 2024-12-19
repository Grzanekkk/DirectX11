#pragma once

#include "MXWindowsSetup.h"

class MXWindow
{
private:
	// singleton for managing window class
	class MXWindowClass
	{
	public:
		static char const* GetName();
		static HINSTANCE GetInstance();

	private:
		MXWindowClass();
		~MXWindowClass();
		static constexpr char const* WindowClassName = "Amazing DirectX Window";
		static MXWindowClass WindowClass;
		HINSTANCE hInstance;
	};

public:
	MXWindow( int const Width, int const Height, char const* Name );
	~MXWindow();
	MXWindow( MXWindow const& ) = delete; // no need for copy constructor

private:
	// Allows to use member function to handle messages
	static LRESULT CALLBACK HandleMsgSetup( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	static LRESULT CALLBACK HandleMsgThunk( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	LRESULT HandleMsg( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

protected:
	int Width = 0;
	int Height = 0;
	HWND hWnd;
};