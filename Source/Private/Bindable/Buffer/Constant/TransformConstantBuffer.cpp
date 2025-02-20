// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/Buffer/Constant/TransformConstantBuffer.h"
#include "Exceptions/MXWindowException.h"
#include "Drawable/Drawable.h"

BTransformConstantBuffer::BTransformConstantBuffer( MXGraphics& Graphics, DDrawable const& InParent )
	: Parent{ InParent }
{
	if( !TransformConstantBuffer )
	{
		TransformConstantBuffer = std::make_unique< BVertexConstantBuffer< DirectX::XMMATRIX > >( Graphics );
	}
}

void BTransformConstantBuffer::Bind( MXGraphics& Graphics )
{
	if( TransformConstantBuffer )
	{
		TransformConstantBuffer->Update( Graphics, DirectX::XMMatrixTranspose( Parent.GetTransformMatrix() * Graphics.GetProjection() ) );
		TransformConstantBuffer->Bind( Graphics );
	}
}

std::unique_ptr< BVertexConstantBuffer< DirectX::XMMATRIX > > BTransformConstantBuffer::TransformConstantBuffer;
