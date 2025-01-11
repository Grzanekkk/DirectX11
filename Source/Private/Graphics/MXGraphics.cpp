// Copyright (c) 2024, Made by Jan Puto :>

#include "Graphics/MXGraphics.h"
#include "Exceptions/MXException.h"
#include "Exceptions/MXWindowException.h"
#include "Graphics/MXGraphicsTypes.h"
#include "d3dcompiler.h"
#include <cmath>

#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dcompiler.lib" )

namespace wrl = Microsoft::WRL;

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

	wrl::ComPtr< ID3D11Resource > BackBuffer = nullptr;
	SwapChain->GetBuffer( 0, __uuidof( ID3D11Resource ), &BackBuffer );
	if( BackBuffer.Get() != nullptr )
	{
		Device->CreateRenderTargetView( BackBuffer.Get(), nullptr, &RenderTargetView );
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
		DeviceContext->ClearRenderTargetView( RenderTargetView.Get(), color );
	}
}

void MXGraphics::DrawTestTriangle( float const angle )
{
	HRESULT hr;
	// clang-format off
	FVertex const Vertices[] = { 
		{ 0.0f, 0.5f, 1.0f, FColor1Bit( 255, 126, 0) },
		{ 0.5f, -0.5f, 1.0f, FColor1Bit( 0, 255, 0 ) },
		{ -0.5f, -0.5f, 1.0f, FColor1Bit( 0, 126, 255 ) }, 
		{ -0.3f, 0.3f, 1.0f, FColor1Bit( 255, 255, 0 ) }, 
		{ 0.3f, 0.3f, 1.0f, FColor1Bit( 255, 0, 255 ) }, 
		{ 0.0f, -0.8f, 1.0f, FColor1Bit( 0, 255, 255 ) } 
	};
	// clang-format on

	UINT const Stride = sizeof( FVertex );
	UINT const Offset = 0u;

	wrl::ComPtr< ID3D11Buffer > VertexBuffer = nullptr;
	D3D11_BUFFER_DESC VertexBufferDesc;
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDesc.CPUAccessFlags = 0u;
	VertexBufferDesc.MiscFlags = 0u;
	VertexBufferDesc.ByteWidth = sizeof( Vertices );
	VertexBufferDesc.StructureByteStride = Stride;

	D3D11_SUBRESOURCE_DATA SubresourceVertexData;
	SubresourceVertexData.pSysMem = Vertices;

	hr = Device->CreateBuffer( &VertexBufferDesc, &SubresourceVertexData, &VertexBuffer );
	if( FAILED( hr ) || VertexBuffer.Get() == nullptr )
	{
		throw MXWND_EXCEPTION( hr );
	}

	DeviceContext->IASetVertexBuffers( 0u, 1, VertexBuffer.GetAddressOf(), &Stride, &Offset );

	// clang-format off
	// Constant buffer for matrix transformation
	struct FConstantBuffer
	{
		struct
		{
			float element[ 4 ][ 4 ];
		} transformation;
	};

	// Figure this out properly
	float AspectRation = 600.f / 800.f;

	FConstantBuffer const ConstantBuffer = 
	{ 
		{
			AspectRation *  std::cos(angle), std::sin(angle), 0.0f, 0.0f,
			AspectRation * -std::sin(angle), std::cos(angle), 0.0f, 0.0f,
							0.0f,			 0.0f,			  1.0f, 0.0f,
							0.0f,			 0.0f,			  0.0f, 1.0f
		}
	};
	
	wrl::ComPtr< ID3D11Buffer > TransformConstBuffer = nullptr;
	D3D11_BUFFER_DESC ConstatnBufferDesc;
	ConstatnBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstatnBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	ConstatnBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstatnBufferDesc.MiscFlags = 0u;
	ConstatnBufferDesc.ByteWidth = sizeof( ConstantBuffer );
	ConstatnBufferDesc.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA ConstBufferData;
	ConstBufferData.pSysMem = &ConstantBuffer;

	hr = Device->CreateBuffer( &ConstatnBufferDesc, &ConstBufferData, &TransformConstBuffer );
	if( FAILED( hr ) || TransformConstBuffer.Get() == nullptr )
	{
		throw MXWND_EXCEPTION( hr );
	}

	DeviceContext->VSSetConstantBuffers( 0u, 1u, TransformConstBuffer.GetAddressOf() );

	// Index buffer
	unsigned short const Indices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 4, 1,
		2, 1, 5,
	};
	// clang-format on

	wrl::ComPtr< ID3D11Buffer > IndexBuffer = nullptr;
	D3D11_BUFFER_DESC IndexBufferDesc;
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.CPUAccessFlags = 0u;
	IndexBufferDesc.MiscFlags = 0u;
	IndexBufferDesc.ByteWidth = sizeof( Indices );
	IndexBufferDesc.StructureByteStride = sizeof( unsigned short );

	D3D11_SUBRESOURCE_DATA SubresourceIndexData;
	SubresourceIndexData.pSysMem = Indices;

	hr = Device->CreateBuffer( &IndexBufferDesc, &SubresourceIndexData, &IndexBuffer );
	if( FAILED( hr ) || IndexBuffer.Get() == nullptr )
	{
		throw MXWND_EXCEPTION( hr );
	}

	DeviceContext->IASetIndexBuffer( IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u );

	// Create PixelShader
	wrl::ComPtr< ID3D11PixelShader > PixelShader = nullptr;
	wrl::ComPtr< ID3DBlob > Blob = nullptr;
	hr = D3DReadFileToBlob( L"Shader/Compiled/PixelShader.cso", &Blob );
	if( FAILED( hr ) )
	{
		throw MXWND_EXCEPTION( hr );
	}

	hr = Device->CreatePixelShader( Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &PixelShader );
	if( FAILED( hr ) )
	{
		throw MXWND_EXCEPTION( hr );
	}

	// Bind created pixel shader
	DeviceContext->PSSetShader( PixelShader.Get(), nullptr, 0u );

	// Create VertexShader
	wrl::ComPtr< ID3D11VertexShader > VertexShader = nullptr;

	hr = D3DReadFileToBlob( L"Shader/Compiled/VertexShader.cso", &Blob );
	if( FAILED( hr ) )
	{
		throw MXWND_EXCEPTION( hr );
	}

	hr = Device->CreateVertexShader( Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &VertexShader );
	if( FAILED( hr ) )
	{
		throw MXWND_EXCEPTION( hr );
	}

	// Bind created vertex shader
	DeviceContext->VSSetShader( VertexShader.Get(), nullptr, 0u );

	// clang-format off
	// Input layout
	wrl::ComPtr< ID3D11InputLayout > InputLayout = nullptr;
	D3D11_INPUT_ELEMENT_DESC const IED[] = { 
		{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 } };
	// clang-format on

	hr = Device->CreateInputLayout( IED, ( UINT ) std::size( IED ), Blob->GetBufferPointer(), Blob->GetBufferSize(), &InputLayout );
	if( FAILED( hr ) )
	{
		throw MXWND_EXCEPTION( hr );
	}

	DeviceContext->IASetInputLayout( InputLayout.Get() );

	// Bind RenderTarget
	DeviceContext->OMSetRenderTargets( 1u, RenderTargetView.GetAddressOf(), nullptr );

	// Set topology type
	DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// Configure viewport
	D3D11_VIEWPORT ViewportConfig;
	ViewportConfig.Width = 800; // FIXME: figure this out properly
	ViewportConfig.Height = 600;
	ViewportConfig.MinDepth = 0;
	ViewportConfig.MaxDepth = 1;
	ViewportConfig.TopLeftX = 0;
	ViewportConfig.TopLeftY = 0;
	DeviceContext->RSSetViewports( 1u, &ViewportConfig );

	// Draw
	// DeviceContext->Draw( ( UINT ) std::size( Vertices ), 0 );
	DeviceContext->DrawIndexed( ( UINT ) std::size( Indices ), 0u, 0u );
}
