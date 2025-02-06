// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "MXWindowsSetup.h"
#include <vector>
#include <d3d11.h>
#include <wrl.h>

namespace wrl = Microsoft::WRL;

class MXGraphics
{
	// This will make life easier 
	friend class BBindable;

public:
	MXGraphics( HWND hWnd, unsigned int const Height, unsigned int const Width );
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

	unsigned int ScreenHeight = 0;
	unsigned int ScreenWidth = 0;
};