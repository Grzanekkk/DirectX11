// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/Buffer/VertexBuffer.h"

void BVertexBuffer::Bind( MXGraphics& Graphics )
{
	// Vertexes will always be the same ( unless i add animations ), no need to bind every frame
	UINT const Offset = 0u;
	GetDeviceContext( Graphics )->IASetVertexBuffers( 0u, 1u, VertexBuffer.GetAddressOf(), &Stride, &Offset );
}
