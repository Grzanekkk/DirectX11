// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Bindable/Bindable.h"
#include "Bindable/Buffer/Constant/ConstantBuffer.h"
#include <DirectXMath.h>
#include <memory>

class DDrawable;

class BTransformConstantBuffer : public BBindable
{
public:
	BTransformConstantBuffer( MXGraphics& Graphics, DDrawable const& InParent );
	void Bind( MXGraphics& Graphics ) override;

private:
	DDrawable const& Parent;
	static std::unique_ptr< BVertexConstantBuffer< DirectX::XMMATRIX > > TransformConstantBuffer;
};