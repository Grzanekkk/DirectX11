// Copyright (c) 2024, Made by Jan Puto :>

#include "Drawable/Shape/Box.h"
#include "Graphics/MXGraphicsTypes.h"
#include "Bindable/Buffer/VertexBuffer.h"
#include "Bindable/Buffer/IndexBuffer.h"
#include "Bindable/InputLayout.h"
#include "Bindable/Topology.h"

DBox::DBox( MXGraphics& Graphics )
{
	// clang-format off
	std::vector< FVertex > Vertices = { 
		{ -1.0f, -1.0f, -1.0f },
		{ 1.0f, -1.0f, -1.0f },
		{ -1.0f, 1.0f, -1.0f },
		{ 1.0f, 1.0f, -1.0f },
		{ -1.0f, -1.0f, 1.0f }, 
		{ 1.0f, -1.0f, 1.0f },
		{ -1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f } };
	// clang-format on

	AddBind( std::make_unique< BVertexBuffer >( Graphics, Vertices ) );

	// Constant buffer for matrix transformation
	// struct FConstantBufferTransform
	//{
	//	dx::XMMATRIX transform;
	//};

	// #FIXME Bind Transform and Color ConstantBuffer

	// clang-format off
	// Index buffer
	std::vector< unsigned short > const Indices = {
		0, 2, 1,	2, 3, 1,
		1, 3, 5,	3, 7, 5,
		2, 6, 3,	3, 6, 7,
		4, 5, 7,	4, 7, 6,
		0, 4, 2,	2, 4, 6,
		0, 1, 4,	1, 5, 4
	};
	// clang-format on

	AddBind( std::make_unique< BIndexBuffer >( Graphics, Indices ) );

	// #FIXME Bind Pixel Shader
	// #FIXME Bind Vertex Shader

	// clang-format off
	// Input layout
	wrl::ComPtr< ID3D11InputLayout > InputLayout = nullptr;
	D3D11_INPUT_ELEMENT_DESC const InputElementDescription[] = { 
		{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	// clang-format on

	// #FIXME Get vertext shader byte code
	// AddBind( std::make_unique< BInputLayout >( Graphics, InputElementDescription ) );

	AddBind( std::make_unique< BTopology >( Graphics, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );
}

void DBox::Tick( float const DeltaTime )
{
}
