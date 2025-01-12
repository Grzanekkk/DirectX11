// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "MXWindowsSetup.h"
#include <d3d11.h>
#include <wrl.h>

class MXGraphics
{
public:
	MXGraphics( HWND hWnd, float const Height, float const Width );
	MXGraphics( MXGraphics const& Other ) = delete;
	MXGraphics& operator=( MXGraphics const& ) = delete;
	~MXGraphics() = default;

public:
	void EndFrame();
	void ClearBuffer( float const R, float const G, float const B );
	void DrawTestTriangle( float const angle, float const X, float const Y );

private:
	Microsoft::WRL::ComPtr< ID3D11Device > Device = nullptr;
	Microsoft::WRL::ComPtr< ID3D11DeviceContext > DeviceContext = nullptr;
	Microsoft::WRL::ComPtr< IDXGISwapChain > SwapChain = nullptr;
	Microsoft::WRL::ComPtr< ID3D11RenderTargetView > RenderTargetView = nullptr;
	Microsoft::WRL::ComPtr< ID3D11DepthStencilView > DepthStencilView = nullptr;

	float ScreenHeight = 0;
	float ScreenWidth = 0;
};