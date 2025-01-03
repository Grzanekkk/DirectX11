// Copyright (c) 2024, Made by Jan Puto :>

#pragma once

struct FColor
{
public:
	FColor( float const R, float const G, float const B );
	float R;
	float G;
	float B;
};

struct FColor1Bit
{
public:
	FColor1Bit( unsigned char const R, unsigned char const G, unsigned char const B, unsigned char const A );
	FColor1Bit( unsigned char const R, unsigned char const G, unsigned char const B );
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
};

struct FVertex
{
public:
	FVertex( float const X, float const Y, float const Z, FColor1Bit const Color );
	float X;
	float Y;
	float Z;
	FColor1Bit Color;
};
