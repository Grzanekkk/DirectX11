// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/Bindable.h"
#include <cassert>

ID3D11DeviceContext* const BBindable::GetDeviceContext( MXGraphics& Graphics )
{
	assert( Graphics.DeviceContext.Get() );
	return Graphics.DeviceContext.Get();
}

ID3D11Device* const BBindable::GetDevice( MXGraphics& Graphics )
{
	assert( Graphics.Device.Get() );
	return Graphics.Device.Get();
}
