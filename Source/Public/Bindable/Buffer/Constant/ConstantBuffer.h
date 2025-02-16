// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Bindable/Bindable.h"
#include "Exceptions/MXWindowException.h"

template< typename ConstType >
class BConstantBuffer : public BBindable
{
public:
	BConstantBuffer( MXGraphics& Graphics, ConstType const& Data )
	{
		D3D11_BUFFER_DESC Descriptor;
		Descriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		Descriptor.Usage = D3D11_USAGE_DYNAMIC;
		Descriptor.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Descriptor.MiscFlags = 0u;
		Descriptor.ByteWidth = sizeof( Data );
		Descriptor.StructureByteStride = 0u;
		D3D11_SUBRESOURCE_DATA SubresourceData = {};
		SubresourceData.pSysMem = &Data;
		HRESULT const hr = GetDevice( Graphics )->CreateBuffer( &Descriptor, &SubresourceData, &ConstantBuffer );
		if( FAILED( hr ) )
		{
			MXWND_EXCEPTION( hr );
		}
	}

	BConstantBuffer( MXGraphics& Graphics )
	{

		D3D11_BUFFER_DESC Descriptor;
		Descriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		Descriptor.Usage = D3D11_USAGE_DYNAMIC;
		Descriptor.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Descriptor.MiscFlags = 0u;
		Descriptor.ByteWidth = sizeof( ConstType );
		Descriptor.StructureByteStride = 0u;

		HRESULT const hr = GetDevice( Graphics )->CreateBuffer( &Descriptor, nullptr, &ConstantBuffer );
		if( FAILED( hr ) )
		{
			MXWND_EXCEPTION( hr );
		}
	}

	void Update( MXGraphics& Graphics, ConstType const& Data )
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		HRESULT const hr = GetDeviceContext( Graphics )->Map( ConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr );

		if( FAILED( hr ) )
		{
			MXWND_EXCEPTION( hr );
		}

		// In this case memcpy is better then std::move because we will be working here with POD, mostly arrays of floats
		memcpy( msr.pData, &Data, sizeof( Data ) );
		GetDeviceContext( Graphics )->Unmap( ConstantBuffer.Get(), 0u );
	}

protected:
	wrl::ComPtr< ID3D11Buffer > ConstantBuffer = nullptr;
};

template< typename ConstType >
class BVertexConstantBuffer : public BConstantBuffer< ConstType >
{
	// Allows compiler to see the constructor
	using BConstantBuffer< ConstType >::BConstantBuffer;

public:
	void Bind( MXGraphics& Graphics ) override
	{
		BBindable::GetDeviceContext( Graphics )->VSSetConstantBuffers( 0u, 1u, BConstantBuffer< ConstType >::ConstantBuffer.GetAddressOf() );
	}
};
template< typename ConstType >
class BPixelConstantBuffer : public BConstantBuffer< ConstType >
{
	// Allows compiler to see the constructor
	using BConstantBuffer< ConstType >::BConstantBuffer;

public:
	void Bind( MXGraphics& Graphics ) override
	{
		BBindable::GetDeviceContext( Graphics )->PSSetConstantBuffers( 0u, 1u, BConstantBuffer< ConstType >::ConstantBuffer.GetAddressOf() );
	}
};
