// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Bindable/Bindable.h"

class BVertexBuffer : public BBindable
{
public:
	template< class VertexType >
	BVertexBuffer( MXGraphics& Graphics, std::vector< VertexType > const& Vertices )
		: Stride( sizeof( VertexType ) )
	{
		wrl::ComPtr< ID3D11Buffer > VertexBuffer = nullptr;
		D3D11_BUFFER_DESC VertexBufferDesc;
		VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		VertexBufferDesc.CPUAccessFlags = 0u;
		VertexBufferDesc.MiscFlags = 0u;
		VertexBufferDesc.ByteWidth = sizeof( VertexType ) * Vertices;
		VertexBufferDesc.StructureByteStride = Stride;

		D3D11_SUBRESOURCE_DATA SubresourceVertexData;
		SubresourceVertexData.pSysMem = Vertices.data();

		HRESULT const hr = GetDevice()->CreateBuffer( &VertexBufferDesc, &SubresourceVertexData, &VertexBuffer );
		if( FAILED( hr ) || VertexBuffer.Get() == nullptr )
		{
			MXWND_EXCEPTION( hr );
		}
	};

	~BVertexBuffer() = default;

	virtual void Bind( MXGraphics& Graphics ) override;

protected:
	wrl::ComPtr< ID3D11Buffer > VertexBuffer = nullptr;
	UINT Stride = 0;
};
