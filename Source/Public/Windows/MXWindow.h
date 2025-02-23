// Copyright (c) 2024, Made by Jan Puto :>

#pragma once

#include "Windows/MXWindowsSetup.h"
#include "Exceptions/MXException.h"
#include "Input/MXKeyboardHandle.h"
#include "Input/MXMouseHandle.h"
#include <optional>
#include <memory>

class MXGraphics;

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

	MXKeyboardHandle& GetKeyboardHandle();
	MXMouseHandle& GetMouseHandle();
	void SetTitle( std::string const& NewTitle );
	std::optional< int > ProcessMessages();
	MXGraphics& GetGraphics();

private:
	// Allows to use member function to handle messages
	static LRESULT CALLBACK HandleMsgSetup( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	static LRESULT CALLBACK HandleMsgThunk( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	LRESULT HandleMsg( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

protected:
	int Width = 0;
	int Height = 0;
	HWND hWnd;
	MXKeyboardHandle KeyboardHandle;
	MXMouseHandle MouseHandle;
	std::unique_ptr< MXGraphics > Graphics = nullptr;
};