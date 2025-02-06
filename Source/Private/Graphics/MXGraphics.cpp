// Copyright (c) 2024, Made by Jan Puto :>

#include "Graphics/MXGraphics.h"
#include "Exceptions/MXException.h"
#include "Exceptions/MXWindowException.h"
#include "Graphics/MXGraphicsTypes.h"
#include "d3dcompiler.h"
#include <cmath>
#include <DirectXMath.h>

#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dcompiler.lib" )

namespace dx = DirectX;

MXGraphics::MXGraphics( HWND hWnd, unsigned int const Height, unsigned int const Width )
{
	ScreenHeight = Height;
	ScreenWidth = Width;

	DXGI_SWAP_CHAIN_DESC SwapChainDescriptor = {};
	SwapChainDescriptor.BufferDesc.Width = ScreenWidth;
	SwapChainDescriptor.BufferDesc.Height = ScreenHeight;
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
		MXWND_EXCEPTION( hr );
	}

	if( DeviceContext == nullptr )
	{
		MX_EXCEPTION( "Failed to create DeviceContext" );
	}

	if( SwapChain == nullptr )
	{
		MX_EXCEPTION( "Failed to create SwapChain" );
	}

	if( Device == nullptr )
	{
		MX_EXCEPTION( "Failed to create Device" );
	}

	wrl::ComPtr< ID3D11Resource > BackBuffer = nullptr;
	hr = SwapChain->GetBuffer( 0, __uuidof( ID3D11Resource ), &BackBuffer );
	if( FAILED( hr ) || BackBuffer.Get() == nullptr )
	{
		MXWND_EXCEPTION( hr );
	}
	Device->CreateRenderTargetView( BackBuffer.Get(), nullptr, &RenderTargetView );

	// Create depth stencil state
	D3D11_DEPTH_STENCIL_DESC DepthStencilDesc = {};
	DepthStencilDesc.DepthEnable = TRUE;
	DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	wrl::ComPtr< ID3D11DepthStencilState > DepthStencilState = nullptr;
	Device->CreateDepthStencilState( &DepthStencilDesc, &DepthStencilState );
	if( FAILED( hr ) || DepthStencilState == nullptr )
	{
		MXWND_EXCEPTION( hr );
	}

	DeviceContext->OMSetDepthStencilState( DepthStencilState.Get(), 1u );

	// Create Depth Texture
	wrl::ComPtr< ID3D11Texture2D > DepthStencilTexture = nullptr;
	D3D11_TEXTURE2D_DESC DepthTextureDesc = {};
	DepthTextureDesc.Height = ScreenHeight;
	DepthTextureDesc.Width = ScreenWidth;
	DepthTextureDesc.MipLevels = 1u;
	DepthTextureDesc.ArraySize = 1u;
	DepthTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;
	DepthTextureDesc.SampleDesc.Count = 1u;
	DepthTextureDesc.SampleDesc.Quality = 0u;
	DepthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	hr = Device->CreateTexture2D( &DepthTextureDesc, nullptr, &DepthStencilTexture );
	if( FAILED( hr ) || DepthStencilTexture == nullptr )
	{
		MXWND_EXCEPTION( hr );
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc = {};
	DSVDesc.Format = DXGI_FORMAT_D32_FLOAT;
	DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DSVDesc.Texture2D.MipSlice = 0u;

	hr = Device->CreateDepthStencilView( DepthStencilTexture.Get(), &DSVDesc, &DepthStencilView );
	if( FAILED( hr ) || DepthStencilView == nullptr )
	{
		MXWND_EXCEPTION( hr );
	}

	// Bind render target
	DeviceContext->OMSetRenderTargets( 1u, RenderTargetView.GetAddressOf(), DepthStencilView.Get() );
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
		DeviceContext->ClearDepthStencilView( DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u );
	}
	else
	{
		MX_EXCEPTION( "DeviceContext is null when trying to ClearBuffer!" );
	}
}

void MXGraphics::DrawTestTriangle( float const angle, float const X, float const Y )
{
	HRESULT hr;
	// clang-format off

	FVertex const Vertices[] = { 
		{ -1.0f, -1.0f, -1.0f },
		{ 1.0f, -1.0f, -1.0f },
		{ -1.0f, 1.0f, -1.0f }, 
		{ 1.0f, 1.0f, -1.0f }, 
		{ -1.0f, -1.0f, 1.0f }, 
		{ 1.0f, -1.0f, 1.0f }, 
		{ -1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f } 
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
		MXWND_EXCEPTION( hr );
	}

	DeviceContext->IASetVertexBuffers( 0u, 1, VertexBuffer.GetAddressOf(), &Stride, &Offset );

	// Constant buffer for matrix transformation
	struct FConstantBufferTransform
	{
		dx::XMMATRIX transform;
	};

	// Figure this out properly
	float const AspectRation = ( float ) ScreenHeight / ( float ) ScreenWidth;

	// clang-format off
	FConstantBufferTransform const ConstantBuffer = {
		// Transpose makes it column major which is what GPU expects
		dx::XMMatrixTranspose( 
			dx::XMMatrixRotationZ( angle ) *
			dx::XMMatrixRotationX( angle ) *
			dx::XMMatrixTranslation( X, 0, Y + 5.f ) *
			dx::XMMatrixPerspectiveFovLH( 1.0f, AspectRation, 0.5f, 20.0f ) 
		)
	};
	// clang-format on

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
		MXWND_EXCEPTION( hr );
	}

	DeviceContext->VSSetConstantBuffers( 0u, 1u, TransformConstBuffer.GetAddressOf() );

	// Face color buffer
	struct FConstantBufferFaceColor
	{
		struct
		{
			float R;
			float G;
			float B;
			float A;

		} FaceColor[ 6 ];
	};

	FConstantBufferFaceColor ConstantBufferFaceColor = { {
		{ 0.9, 0.7, 0.8 },
		{ 0.7, 0.9, 0.7 },
		{ 0.7, 0.8, 1.0 },
		{ 1.0, 0.9, 0.7 },
		{ 0.8, 0.7, 1.0 },
		{ 0.9, 1.0, 0.7 },
	} };

	wrl::ComPtr< ID3D11Buffer > FaceColorConstBuffer = nullptr;
	D3D11_BUFFER_DESC FaceColorConstBufferDesc;
	FaceColorConstBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	FaceColorConstBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	FaceColorConstBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	FaceColorConstBufferDesc.MiscFlags = 0u;
	FaceColorConstBufferDesc.ByteWidth = sizeof( ConstantBufferFaceColor );
	FaceColorConstBufferDesc.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA FaceColorConstBufferData;
	FaceColorConstBufferData.pSysMem = &ConstantBufferFaceColor;

	hr = Device->CreateBuffer( &FaceColorConstBufferDesc, &FaceColorConstBufferData, &FaceColorConstBuffer );
	if( FAILED( hr ) || FaceColorConstBuffer.Get() == nullptr )
	{
		MXWND_EXCEPTION( hr );
	}

	DeviceContext->PSSetConstantBuffers( 0u, 1u, FaceColorConstBuffer.GetAddressOf() );

	// clang-format off
	// Index buffer
	unsigned short const Indices[] = {
		0, 2, 1,	2, 3, 1,
		1, 3, 5,	3, 7, 5,
		2, 6, 3,	3, 6, 7,
		4, 5, 7,	4, 7, 6,
		0, 4, 2,	2, 4, 6,
		0, 1, 4,	1, 5, 4
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
		MXWND_EXCEPTION( hr );
	}

	DeviceContext->IASetIndexBuffer( IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u );

	// Create PixelShader
	wrl::ComPtr< ID3D11PixelShader > PixelShader = nullptr;
	wrl::ComPtr< ID3DBlob > Blob = nullptr;
	hr = D3DReadFileToBlob( L"Shader/Compiled/PixelShader.cso", &Blob );
	if( FAILED( hr ) )
	{
		MXWND_EXCEPTION( hr );
	}

	hr = Device->CreatePixelShader( Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &PixelShader );
	if( FAILED( hr ) )
	{
		MXWND_EXCEPTION( hr );
	}

	// Bind created pixel shader
	DeviceContext->PSSetShader( PixelShader.Get(), nullptr, 0u );

	// Create VertexShader
	wrl::ComPtr< ID3D11VertexShader > VertexShader = nullptr;

	hr = D3DReadFileToBlob( L"Shader/Compiled/VertexShader.cso", &Blob );
	if( FAILED( hr ) )
	{
		MXWND_EXCEPTION( hr );
	}

	hr = Device->CreateVertexShader( Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &VertexShader );
	if( FAILED( hr ) )
	{
		MXWND_EXCEPTION( hr );
	}

	// Bind created vertex shader
	DeviceContext->VSSetShader( VertexShader.Get(), nullptr, 0u );

	// clang-format off
	// Input layout
	wrl::ComPtr< ID3D11InputLayout > InputLayout = nullptr;
	D3D11_INPUT_ELEMENT_DESC const IED[] = { 
		{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	// clang-format on

	hr = Device->CreateInputLayout( IED, ( UINT ) std::size( IED ), Blob->GetBufferPointer(), Blob->GetBufferSize(), &InputLayout );
	if( FAILED( hr ) )
	{
		MXWND_EXCEPTION( hr );
	}

	DeviceContext->IASetInputLayout( InputLayout.Get() );

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
	DeviceContext->DrawIndexed( ( UINT ) std::size( Indices ), 0u, 0u );
}
