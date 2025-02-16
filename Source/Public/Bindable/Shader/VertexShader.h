// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Bindable/Shader/ShaderBase.h"

class BVertexShader : public BShaderBase
{
public:
	BVertexShader( MXGraphics& Graphics, std::wstring const& ShaderPath );
	void Bind( MXGraphics& Graphics ) override;

protected:
	wrl::ComPtr< ID3D11VertexShader > VertexShader = nullptr;
};
