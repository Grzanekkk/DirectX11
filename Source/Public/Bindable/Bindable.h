// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Graphics/MXGraphics.h"

class BBindable
{
public:
	BBindable() = default;
	~BBindable() = default;

	virtual void Bind( MXGraphics& Graphics );
};
