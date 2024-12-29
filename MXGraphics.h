// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "MXWindowsSetup.h"
#include <d3d11.h>

class MXGraphics
{
public:
	MXGraphics( HWND hWnd );
	MXGraphics( MXGraphics const& Other ) = delete;
	MXGraphics& operator=( MXGraphics const& ) = delete;
	~MXGraphics();

public:
	void EndFrame();
	void ClearBuffer( float const R, float const G, float const B );

private:
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;
	IDXGISwapChain* SwapChain = nullptr;
	ID3D11RenderTargetView* RenderTargetView = nullptr;
};