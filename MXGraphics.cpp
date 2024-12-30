// Copyright (c) 2024, Made by Jan Puto :>

#include "MXGraphics.h"
#include "MXException.h"
#include "MXWindowException.h"

#pragma comment( lib, "d3d11.lib" )

MXGraphics::MXGraphics( HWND hWnd )
{
	DXGI_SWAP_CHAIN_DESC SwapChainDescriptor = {};
	SwapChainDescriptor.BufferDesc.Width = 0; // Figure it out
	SwapChainDescriptor.BufferDesc.Height = 0;
	SwapChainDescriptor.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Maybe use BGRA?
	SwapChainDescriptor.BufferDesc.RefreshRate.Numerator = 0;			// Use device refresh rate
	SwapChainDescriptor.BufferDesc.RefreshRate.Denominator = 0;
	SwapChainDescriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDescriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDescriptor.SampleDesc.Count = 1;	// Turn off anti aliasing
	SwapChainDescriptor.SampleDesc.Quality = 0; // Turn off anti aliasing
	SwapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDescriptor.BufferCount = 1; // Makes 2 buffer so we can use double buffering
	SwapChainDescriptor.OutputWindow = hWnd;
	SwapChainDescriptor.Windowed = TRUE;
	SwapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDescriptor.Flags = 0;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION, &SwapChainDescriptor, &SwapChain, &Device, nullptr, &DeviceContext );

	if( FAILED( hr ) )
	{
		throw MXWND_EXCEPTION( hr );
	}

	if( DeviceContext == nullptr )
	{
		throw MX_EXCEPTION( "Failed to create DeviceContext" );
	}

	if( SwapChain == nullptr )
	{
		throw MX_EXCEPTION( "Failed to create SwapChain" );
	}

	if( Device == nullptr )
	{
		throw MX_EXCEPTION( "Failed to create Device" );
	}

	ID3D11Resource* BackBuffer = nullptr;
	SwapChain->GetBuffer( 0, __uuidof( ID3D11Resource ), reinterpret_cast< void** >( &BackBuffer ) );
	if( BackBuffer )
	{
		Device->CreateRenderTargetView( BackBuffer, nullptr, &RenderTargetView );
		BackBuffer->Release();
	}
}

MXGraphics::~MXGraphics()
{
	if( RenderTargetView != nullptr )
	{
		RenderTargetView->Release();
	}

	if( DeviceContext != nullptr )
	{
		DeviceContext->Release();
	}

	if( SwapChain != nullptr )
	{
		SwapChain->Release();
	}

	if( Device != nullptr )
	{
		Device->Release();
	}
}

void MXGraphics::EndFrame()
{
	SwapChain->Present( 1u, 0u );
}

void MXGraphics::ClearBuffer( float const R, float const G, float const B )
{
	float const color[] = { R, G, B, 1.f };
	if( DeviceContext )
	{
		DeviceContext->ClearRenderTargetView( RenderTargetView, color );
	}
}
