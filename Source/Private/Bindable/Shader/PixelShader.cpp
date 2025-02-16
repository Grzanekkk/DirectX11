// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/Shader/PixelShader.h"
#include "Exceptions/MXWindowException.h"

BPixelShader::BPixelShader( MXGraphics& Graphics, std::wstring const& ShaderPath )
	: BShaderBase::BShaderBase( Graphics, ShaderPath )
{
	if( ShaderBytecodeBlob )
	{
		HRESULT const hr = GetDevice( Graphics )->CreatePixelShader( ShaderBytecodeBlob->GetBufferPointer(), ShaderBytecodeBlob->GetBufferSize(), nullptr, &PixelShader );
		if( FAILED( hr ) )
		{
			MXWND_EXCEPTION( hr );
		}
	}
	else
	{
		MX_EXCEPTION( "Trying to create Pixel shader but code blob is invalid!" );
	}
}

void BPixelShader::Bind( MXGraphics& Graphics )
{
	if( PixelShader )
	{
		GetDeviceContext( Graphics )->PSSetShader( PixelShader.Get(), nullptr, 0u );
	}
	else
	{
		MX_EXCEPTION( "Trying to bind Pixel shader but ID3D11PixelShader ptr is invalid!" );
	}
}
