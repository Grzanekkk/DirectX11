// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/Buffer/IndexBuffer.h"
#include "Exceptions/MXWindowException.h"

BIndexBuffer::BIndexBuffer( MXGraphics& Graphics, std::vector< unsigned short > const& Indices )
	: IndexCount{ Indices.size() }
{
	D3D11_BUFFER_DESC IndexBufferDesc;
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.CPUAccessFlags = 0u;
	IndexBufferDesc.MiscFlags = 0u;
	IndexBufferDesc.ByteWidth = sizeof( Indices );
	IndexBufferDesc.StructureByteStride = sizeof( unsigned short );

	D3D11_SUBRESOURCE_DATA SubresourceIndexData;
	SubresourceIndexData.pSysMem = Indices.data();

	HRESULT const hr = GetDevice( Graphics )->CreateBuffer( &IndexBufferDesc, &SubresourceIndexData, &IndexBuffer );
	if( FAILED( hr ) || IndexBuffer.Get() == nullptr )
	{
		MXWND_EXCEPTION( hr );
	}
}

void BIndexBuffer::Bind( MXGraphics& Graphics )
{
	GetDeviceContext( Graphics )->IASetIndexBuffer( IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u );
}

unsigned int BIndexBuffer::GetCount() const
{
	return IndexCount;
}
