// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/InputLayout.h"
#include "Exceptions/MXWindowException.h"

BInputLayout::BInputLayout( MXGraphics& Graphics, std::vector< D3D11_INPUT_ELEMENT_DESC > const& Layout, ID3DBlob* const VertexShaderBytecode )
{
	if( VertexShaderBytecode )
	{
		HRESULT const hr =
			GetDevice( Graphics )
				->CreateInputLayout( Layout.data(), ( UINT ) Layout.size(), VertexShaderBytecode->GetBufferPointer(), VertexShaderBytecode->GetBufferSize(), &InputLayout );

		if( FAILED( hr ) )
		{
			MXWND_LAST_EXCEPTION();
		}
	}
	else
	{
		MX_EXCEPTION( "Invalid shader byte code!" );
	}
}

void BInputLayout::Bind( MXGraphics& Graphics )
{
	GetDeviceContext( Graphics )->IASetInputLayout( InputLayout.Get() );
}
