// Copyright (c) 2024, Made by Jan Puto :>

#include "Bindable/Bindable.h"


ID3D11DeviceContext* const BBindable::GetDeviceContext( MXGraphics& Graphics )
{
	return Graphics.DeviceContext.Get();
}

ID3D11Device* const BBindable::GetDevice( MXGraphics& Graphics )
{
	return Graphics.Device.Get();
}
