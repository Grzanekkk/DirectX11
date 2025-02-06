// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Bindable/Bindable.h"

class BInputLayout : public BBindable
{
public:
	BInputLayout( MXGraphics& Graphics, std::vector< D3D11_INPUT_ELEMENT_DESC > const& Layout, ID3DBlob* VertexShaderBytecode );
	void Bind( MXGraphics& Graphics ) override;

protected:
	wrl::ComPtr< ID3D11InputLayout > InputLayout = nullptr;
};
