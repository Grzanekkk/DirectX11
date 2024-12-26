// Copyright (c) 2024, Made by Jan Puto :>

#pragma once

#include "MXWindowsSetup.h"
#include "MXException.h"
#include "MXKeyboardHandle.h"
#include "MXMouseHandle.h"
#include <optional>

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

	class MXWindowException : public MXException
	{
	public:
		MXWindowException( int const Line, char const* File, HRESULT const hr );
		char const* what() const override;
		virtual char const* GetType() const override;
		HRESULT GetErrorCode() const;
		virtual std::string GetErrorMessage() const override;
		static std::string TranstaleErrorCode( HRESULT const hr );

	protected:
		HRESULT hr;
	};

public:
	MXWindow( int const Width, int const Height, char const* Name );
	~MXWindow();
	MXWindow( MXWindow const& ) = delete; // no need for copy constructor

	MXKeyboardHandle& GetKeyboardHandle();
	MXMouseHandle& GetMouseHandle();
	void SetTitle( std::string const& NewTitle );
	std::optional< int > ProcessMessages();

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
};

#define MXWND_EXCEPTION( hr ) MXWindow::MXWindowException( __LINE__, __FILE__, hr )
#define MXWND_LAST_EXCEPTION() MXWindow::MXWindowException( __LINE__, __FILE__, GetLastError() )