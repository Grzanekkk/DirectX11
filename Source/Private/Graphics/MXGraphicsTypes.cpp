// Copyright (c) 2024, Made by Jan Puto :>

#include "Graphics/MXGraphicsTypes.h"

FVertex::FVertex( float const X, float const Y, float const Z )
	: X{ X }
	, Y{ Y }
	, Z{ Z }
{
}

FColor::FColor( float const R, float const G, float const B )
	: R{ R }
	, G{ G }
	, B{ B }
{
}

FColor1Bit::FColor1Bit( unsigned char const R, unsigned char const G, unsigned char const B, unsigned char const A )
	: R{ R }
	, G{ G }
	, B{ B }
	, A{ A }
{
}

FColor1Bit::FColor1Bit( unsigned char const R, unsigned char const G, unsigned char const B )
	: R{ R }
	, G{ G }
	, B{ B }
	, A{ 0 }
{
}
