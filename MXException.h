#pragma once

#include <exception>
#include <string>

class MXException : public std::exception
{
public:
	MXException( int const Line, char const* File );
	char const* what() const override;
	virtual char const* GetType() const;
	int GetLine() const;
	std::string const& GetFile() const;
	std::string GetOriginString() const;

private:
	int Line = -1;
	std::string File;

protected:
	// its mutalbe so we can set this in what()
	mutable std::string WhatBuffer;
};

#define MX_EXCEPTION( hr ) MXException( __LINE__, __FILE__ )