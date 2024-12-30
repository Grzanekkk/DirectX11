// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "MXWindowsSetup.h"
#include "MXException.h"

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

#define MXWND_EXCEPTION( hr ) MXWindowException( __LINE__, __FILE__, hr )
#define MXWND_LAST_EXCEPTION() MXWindowException( __LINE__, __FILE__, GetLastError() )