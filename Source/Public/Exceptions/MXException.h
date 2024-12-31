// Copyright (c) 2024, Made by Jan Puto :>

#pragma once

#include <exception>
#include <string>

class MXException : public std::exception
{
public:
	MXException( int const Line, char const* File, char const* const Message );
	MXException( int const Line, char const* File );
	char const* what() const override;
	virtual char const* GetType() const;
	int GetLine() const;
	std::string const& GetFile() const;
	std::string GetOriginString() const;
	virtual std::string GetErrorMessage() const;

private:
	int Line = -1;
	std::string File;
	std::string Message;

protected:
	// its mutalbe so we can set this in what()
	mutable std::string WhatBuffer;
};

#define MX_EXCEPTION( Message ) MXException( __LINE__, __FILE__, Message )