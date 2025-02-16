// Copyright (c) 2024, Made by Jan Puto :>

#include "Exceptions/MXWindowException.h"
#include <sstream>

MXWindowException::MXWindowException( int const Line, char const* File, HRESULT const hr )
	: MXException{ Line, File }
	, hr{ hr }
{
}

char const* MXWindowException::what() const
{
	std::ostringstream ErrorString;
	ErrorString << GetType() << std::endl << "[ErrorCode] " << GetErrorCode() << std::endl << "[Description] " << GetErrorMessage() << std::endl << GetOriginString();
	WhatBuffer = ErrorString.str();
	return WhatBuffer.c_str();
}

char const* MXWindowException::GetType() const
{
	return "MX Window Exception";
}

HRESULT MXWindowException::GetErrorCode() const
{
	return hr;
}

std::string const MXWindowException::GetErrorMessage() const
{
	return TranstaleErrorCode( hr );
}

std::string MXWindowException::TranstaleErrorCode( HRESULT const hr )
{
	char* MessageBuffer = nullptr;
	DWORD Messagelen = FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr,
		MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), reinterpret_cast< LPSTR >( &MessageBuffer ), 0, nullptr );

	if( Messagelen == 0 )
	{
		return "Unknown error code";
	}

	std::string const& ErrorString = MessageBuffer;
	LocalFree( MessageBuffer );

	return ErrorString;
}
