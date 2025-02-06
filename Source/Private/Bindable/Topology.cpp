// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/Topology.h"
#include "Exceptions/MXWindowException.h"

BTopology::BTopology( MXGraphics& Graphice, D3D11_PRIMITIVE_TOPOLOGY const InType )
	: Type{ InType }
{
}

void BTopology::Bind( MXGraphics& Graphice )
{
	GetDeviceContext( Graphice )->IASetPrimitiveTopology( Type );
}
