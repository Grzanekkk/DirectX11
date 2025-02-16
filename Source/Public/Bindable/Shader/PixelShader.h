// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Bindable/Shader/ShaderBase.h"

class BPixelShader: public BShaderBase
{
public:
	BPixelShader( MXGraphics& Graphics, std::wstring const& ShaderPath );
	void Bind( MXGraphics& Graphics ) override;

protected:
	wrl::ComPtr< ID3D11PixelShader > PixelShader = nullptr;
};
