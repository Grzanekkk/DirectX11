// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/Shader/VertexShader.h"
#include "Exceptions/MXWindowException.h"

BVertexShader::BVertexShader( MXGraphics& Graphics, std::wstring const& ShaderPath )
	: BShaderBase::BShaderBase( Graphics, ShaderPath )
{
	if( ShaderBytecodeBlob )
	{
		HRESULT const hr = GetDevice( Graphics )->CreateVertexShader( ShaderBytecodeBlob->GetBufferPointer(), ShaderBytecodeBlob->GetBufferSize(), nullptr, &VertexShader );
		if( FAILED( hr ) )
		{
			MXWND_EXCEPTION( hr );
		}
	}
	else
	{
		MX_EXCEPTION( "Trying to create Vertex shader but code blob is invalid!" );
	}
}

void BVertexShader::Bind( MXGraphics& Graphics )
{
	if( VertexShader )
	{
		GetDeviceContext( Graphics )->VSSetShader( VertexShader.Get(), nullptr, 0u );
	}
	else
	{
		MX_EXCEPTION( "Trying to bind Vertex shader but ID3D11VertexShader ptr is invalid!" );
	}
}
