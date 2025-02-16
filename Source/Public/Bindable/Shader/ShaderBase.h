// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Bindable/Bindable.h"

class BShaderBase : public BBindable
{
public:
	// ShaderPath is wstr because D3DReadFileToBlob requires it
	BShaderBase( MXGraphics& Graphics, std::wstring const& ShaderPath );
	void Bind( MXGraphics& gfx ) override;

	ID3DBlob* const GetBytecode() const;

protected:
	wrl::ComPtr< ID3DBlob > ShaderBytecodeBlob = nullptr;
};
