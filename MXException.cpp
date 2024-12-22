#include "MXException.h"
#include <sstream>

MXException::MXException( int const Line, char const* file )
	: Line{ Line }
	, File{ File }
{
}

char const* MXException::what() const
{
	std::ostringstream ErrorString;
	ErrorString << GetType() << std::endl << GetOriginString();
	WhatBuffer = ErrorString.str();
	return WhatBuffer.c_str();
}

char const* MXException::GetType() const
{
	return "Regular MX Exception";
}

int MXException::GetLine() const
{
	return Line;
}

std::string const& MXException::GetFile() const
{
	return File;
}

std::string MXException::GetOriginString() const
{
	std::ostringstream ErrorString;
	ErrorString << "[File] " << File << std::endl << "[Line] " << Line;
	return ErrorString.str();
}
