// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/Index/VertexBuffer.h"
#include "Exceptions/MXWindowException.h"

void BVertexBuffer::Bind( MXGraphics& Graphics )
{
	UINT const Offset = 0u;
	GetDeviceContext( Graphics )->IASetVertexBuffers( 0u, 1u, VertexBuffer.GetAddressOf(), &Stride, &Offset );
}
