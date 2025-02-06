// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Bindable/Bindable.h"

class BTopology : public BBindable
{

public:
	BTopology( MXGraphics& Graphice, D3D11_PRIMITIVE_TOPOLOGY const InType );
	void Bind( MXGraphics& Graphice ) override;

protected:
	D3D11_PRIMITIVE_TOPOLOGY Type;
};
