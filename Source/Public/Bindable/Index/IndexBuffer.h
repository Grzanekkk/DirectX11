// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Bindable/Bindable.h"

class BIndexBuffer : BBindable
{
public:
	BIndexBuffer( MXGraphics& Graphics, std::vector< unsigned short > const& Indices );
	~BIndexBuffer() = default;

	virtual void Bind( MXGraphics& Graphics ) override;
	unsigned int GetCount() const;

protected:
	wrl::ComPtr< ID3D11Buffer > IndexBuffer = nullptr;
	unsigned int IndexCount = -1;
};
