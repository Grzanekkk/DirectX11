// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/Shader/ShaderBase.h"
#include "Exceptions/MXWindowException.h"
#include "d3dcompiler.h"

BShaderBase::BShaderBase( MXGraphics& Graphics, std::wstring const& ShaderPath )
{
	HRESULT const hr = D3DReadFileToBlob( ShaderPath.c_str(), &ShaderBytecodeBlob );
	if( FAILED( hr ) )
	{
		MXWND_EXCEPTION( hr );
	}
}

void BShaderBase::Bind( MXGraphics& gfx )
{
}

ID3DBlob* const BShaderBase::GetBytecode() const
{
	return ShaderBytecodeBlob.Get();
}
