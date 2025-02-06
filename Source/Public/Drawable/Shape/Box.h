// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Drawable/Drawable.h"

class DBox : public DDrawable
{
public:
	DBox( MXGraphics& Graphics );
	DBox( DDrawable const& ) = delete;
	~DBox() = default;

	virtual void Tick( float const DeltaTime ) override;
};