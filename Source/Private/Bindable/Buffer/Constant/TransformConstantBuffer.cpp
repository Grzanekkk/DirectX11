// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/Buffer/Constant/TransformConstantBuffer.h"
#include "Exceptions/MXWindowException.h"
#include "Drawable/Drawable.h"

BTransformConstantBuffer::BTransformConstantBuffer( MXGraphics& Graphics, DDrawable const& InParent )
	: Parent{ InParent }
	, TransformBuffer{ Graphics }
{
}

void BTransformConstantBuffer::Bind( MXGraphics& Graphics )
{
	TransformBuffer.Update( Graphics, DirectX::XMMatrixTranspose( Parent.GetTransformMatrix() * Graphics.GetProjection() ) );
	TransformBuffer.Bind( Graphics );
}
