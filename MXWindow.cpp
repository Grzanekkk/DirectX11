// Copyright (c) 2024, Made by Jan Puto :>

#include "MXWindow.h"
#include <sstream>
#include "resource.h"
#include "Windowsx.h"
#include "MXGraphics.h"

MXWindow::MXWindowClass MXWindow::MXWindowClass::WindowClass;

MXWindow::MXWindow( int const Width, int const Height, char const* Name )
	: Width{ Width }
	, Height{ Height }

{
	// calc window size
	RECT rect;
	rect.left = 100;
	rect.right = Width + rect.left;
	rect.top = 100;
	rect.bottom = Height + rect.top;
	AdjustWindowRect( &rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE );

	hWnd = CreateWindow( MXWindow::MXWindowClass::GetName(), Name, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left,
		rect.bottom - rect.top, nullptr, nullptr, MXWindowClass::GetInstance(), this ); // Passing *this* as user param is SUPER important later

	if( hWnd == nullptr )
	{
		throw MXWND_LAST_EXCEPTION();
	}

	ShowWindow( hWnd, SW_SHOWDEFAULT );

	// Makes Graphics handle object for handling all graphics stuff (D11)
	Graphics = std::make_unique< MXGraphics >( hWnd );
}

MXWindow::~MXWindow()
{
	DestroyWindow( hWnd );
}

MXKeyboardHandle& MXWindow::GetKeyboardHandle()
{
	return KeyboardHandle;
}

MXMouseHandle& MXWindow::GetMouseHandle()
{
	return MouseHandle;
}

void MXWindow::SetTitle( std::string const& NewTitle )
{
	if( SetWindowText( hWnd, NewTitle.c_str() ) == 0 )
	{
		throw MXWND_LAST_EXCEPTION();
	}
}

std::optional< int > MXWindow::ProcessMessages()
{
	MSG Msg;
	while( PeekMessage( &Msg, nullptr, 0, 0, PM_REMOVE ) )
	{
		if( Msg.message == WM_QUIT )
		{
			return Msg.wParam;
		}

		TranslateMessage( &Msg );
		DispatchMessage( &Msg );
	}

	return {};
}

MXGraphics& MXWindow::GetGraphics()
{
	MXGraphics* const GraphicsPtr = Graphics.get();
	if( Graphics == nullptr )
	{
		throw MX_EXCEPTION( "Graphics [MXGraphics] is not valid" );
	}

	return *Graphics;
}

MXWindow::MXWindowClass::MXWindowClass()
	: hInstance( GetModuleHandle( nullptr ) )
{
	char const* const ClassName = GetName();
	WNDCLASSEX WindowsClass = { 0 };
	WindowsClass.cbSize = sizeof( WindowsClass );
	WindowsClass.style = CS_OWNDC;
	WindowsClass.lpfnWndProc = HandleMsgSetup;
	WindowsClass.cbClsExtra = 0;
	WindowsClass.cbWndExtra = 0;
	WindowsClass.hInstance = hInstance;
	WindowsClass.hIcon = static_cast< HICON >( LoadImage( hInstance, MAKEINTRESOURCE( IDI_ICON2 ), IMAGE_ICON, 32, 32, 0 ) );
	WindowsClass.hCursor = nullptr;
	WindowsClass.hbrBackground = nullptr;
	WindowsClass.lpszMenuName = nullptr;
	WindowsClass.lpszClassName = ClassName;
	WindowsClass.hIconSm = static_cast< HICON >( LoadImage( hInstance, MAKEINTRESOURCE( IDI_ICON2 ), IMAGE_ICON, 16, 16, 0 ) );

	RegisterClassEx( &WindowsClass );
}

MXWindow::MXWindowClass::~MXWindowClass()
{
	UnregisterClass( WindowClassName, GetInstance() );
}

LRESULT MXWindow::HandleMsgSetup( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if( msg == WM_NCCREATE )
	{
		// extract ptr to created MXWindow
		CREATESTRUCTW const* const CreateStruct = reinterpret_cast< CREATESTRUCTW* >( lParam );
		if( CreateStruct )
		{
			MXWindow* const CreatedWindow = static_cast< MXWindow* >( CreateStruct->lpCreateParams );
			if( CreatedWindow )
			{
				// retarget message handling
				SetWindowLongPtr( hWnd, GWLP_USERDATA, reinterpret_cast< LONG_PTR >( CreatedWindow ) );
				SetWindowLongPtr( hWnd, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( &MXWindow::HandleMsgThunk ) );

				return CreatedWindow->HandleMsg( hWnd, msg, wParam, lParam );
			}
			else
			{
				// Print Error
			}
		}
		else
		{
			// Print Error
		}
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

LRESULT MXWindow::HandleMsgThunk( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	MXWindow* const Window = reinterpret_cast< MXWindow* >( GetWindowLongPtr( hWnd, GWLP_USERDATA ) );
	if( Window )
	{
		Window->HandleMsg( hWnd, msg, wParam, lParam );
	}

	// Print Error
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

LRESULT MXWindow::HandleMsg( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
		case WM_CLOSE:
			PostQuitMessage( 0 );
			return 0;
		case WM_KILLFOCUS:
			KeyboardHandle.ClearState();
			break;
		/// *** Keybaord handle *** ///
		case WM_KEYDOWN:
		// handle ALT and F-keys
		case WM_SYSKEYDOWN:
			// lParam & 0x40000000 checks bit 30
			if( !( lParam & 0x40000000 || KeyboardHandle.IsAutorepeatEnaled() ) )
			{
				KeyboardHandle.OnKeyPressed( static_cast< unsigned char >( wParam ) );
			}
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			KeyboardHandle.OnKeyReleased( static_cast< unsigned char >( wParam ) );
			break;
		case WM_CHAR:
			KeyboardHandle.OnChar( static_cast< unsigned char >( wParam ) );
			break;
		/// *** Mouse handle *** ///
		case WM_LBUTTONDOWN:
			MouseHandle.OnLMBPressed( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
			break;
		case WM_LBUTTONUP:
			MouseHandle.OnLMBReleased( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
			break;
		case WM_RBUTTONDOWN:
			MouseHandle.OnRMBPressed( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
			break;
		case WM_RBUTTONUP:
			MouseHandle.OnRMBReleased( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
			break;
		case WM_MOUSEWHEEL: {
			int const zDelta = GET_WHEEL_DELTA_WPARAM( wParam );
			if( zDelta > 0 )
			{
				MouseHandle.OnWheelUp( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
			}
			else if( zDelta < 0 )
			{
				MouseHandle.OnWheelDown( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
			}
			break;
		}
		case WM_MOUSEMOVE: {
			POINTS const pt MAKEPOINTS( lParam );
			// Handle mouse movement inside client region
			if( pt.x >= 0 && pt.x < Width && pt.y >= 0 && pt.y < Height )
			{
				MouseHandle.OnMouseMove( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
				if( !MouseHandle.IsMouseInWindow() )
				{
					SetCapture( hWnd );
					MouseHandle.OnMouseEnterWindow();
				}
			}
			// Handle mouse movement outside client region
			else
			{
				if( MouseHandle.IsLMBPressed() || MouseHandle.IsRMBPressed() )
				{
					MouseHandle.OnMouseMove( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );
				}
				else
				{
					ReleaseCapture();
					MouseHandle.OnMouseLeaveWindow();
				}
			}

			break;
		}
			// case WM_MOUSELEAVE
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

char const* MXWindow::MXWindowClass::GetName()
{
	return WindowClassName;
}

HINSTANCE MXWindow::MXWindowClass::GetInstance()
{
	return WindowClass.hInstance;
}

MXWindow::MXWindowException::MXWindowException( int const Line, char const* File, HRESULT const hr )
	: MXException{ Line, File }
	, hr{ hr }
{
}

char const* MXWindow::MXWindowException::what() const
{
	std::ostringstream ErrorString;
	ErrorString << GetType() << std::endl << "[ErrorCode] " << GetErrorCode() << std::endl << "[Description] " << GetErrorMessage() << std::endl << GetOriginString();
	WhatBuffer = ErrorString.str();
	return WhatBuffer.c_str();
}

char const* MXWindow::MXWindowException::GetType() const
{
	return "MX Window Exception";
}

HRESULT MXWindow::MXWindowException::GetErrorCode() const
{
	return hr;
}

std::string MXWindow::MXWindowException::GetErrorMessage() const
{
	return TranstaleErrorCode( hr );
}

std::string MXWindow::MXWindowException::TranstaleErrorCode( HRESULT const hr )
{
	char* MessageBuffer = nullptr;
	DWORD Messagelen = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr,
		MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), reinterpret_cast< LPSTR >( &MessageBuffer ), 0, nullptr );

	if( Messagelen == 0 )
	{
		return "Unknown error code";
	}

	std::string const ErrorString = MessageBuffer;
	LocalFree( MessageBuffer );

	return ErrorString;
}
