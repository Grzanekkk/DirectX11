// Copyright (c) 2024, Made by Jan Puto :>

#include "MXWindow.h"
#include <iostream>
#include <sstream>

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	try
	{
		MXWindow WindowHandle( 800, 600, "TOYOTA" );

		// Message pump
		MSG Msg;
		BOOL gResult = -1;
		// gResult == 0 is posted when QUIT msg is send
		while( ( gResult = GetMessage( &Msg, nullptr, 0, 0 ) ) > 0 )
		{
			TranslateMessage( &Msg );
			DispatchMessage( &Msg );

			if( WindowHandle.GetKeyboardHandle().IsKeyPressed( VK_MENU ) )
			{
				MessageBox( nullptr, "SPACE SPACE", "SPACE", MB_OK || MB_ICONHAND );
			}

			MXMouseHandle& MouseHandle = WindowHandle.GetMouseHandle();
			if( !MouseHandle.IsEmpty() )
			{
				MXMouseHandleEvent const& Event = MouseHandle.Read().value();
				if( Event.IsValid() )
				{
					if( Event.GetEventType() == MXMouseHandleEvent::EMXMouseHandleEventType::Move )
					{
						std::ostringstream oss;
						oss << "Mouse Position: (" << Event.GetPosX() << ", " << Event.GetPosY() << ")";
						WindowHandle.SetTitle( oss.str() );
					}
				}
			}
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

	return 0;
}