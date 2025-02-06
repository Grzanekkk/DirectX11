// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Bindable/Bindable.h"
class DDrawable;

class BTransformConstantBuffer : public BBindable
{
public:
	BTransformConstantBuffer( MXGraphics& Graphics, DDrawable const& InParent );
	void Bind( MXGraphics& Graphics ) override;

private:
	DDrawable const& Parent;
};
