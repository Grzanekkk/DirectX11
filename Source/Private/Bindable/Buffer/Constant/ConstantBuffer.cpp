// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/Buffer/Constant/TransformConstantBuffer.h"
#include "Exceptions/MXWindowException.h"

BTransformConstantBuffer::BTransformConstantBuffer( MXGraphics& Graphics, DDrawable const& InParent )
	: Parent{ InParent }
{
}

void BTransformConstantBuffer::Bind( MXGraphics& Graphics )
{
}
