// Copyright (c) 2024, Made by Jan Puto :>

#include "Drawable/Shape/Pyramid.h"
#include "Graphics/MXGraphicsTypes.h"
#include "Bindable/Buffer/VertexBuffer.h"
#include "Bindable/Buffer/IndexBuffer.h"
#include "Bindable/Buffer/Constant/ConstantBuffer.h"
#include "Bindable/Buffer/Constant/TransformConstantBuffer.h"
#include "Bindable/InputLayout.h"
#include "Bindable/Topology.h"
#include "Bindable/Shader/VertexShader.h"
#include "Bindable/Shader/PixelShader.h"

DPyramid::DPyramid( MXGraphics& Graphics, std::mt19937& Rng, std::uniform_real_distribution< float >& AngleRand, std::uniform_real_distribution< float >& SpeedRand,
	std::uniform_real_distribution< float >& OrbitRand, std::uniform_real_distribution< float >& RadiusRand )
	: r( RadiusRand( Rng ) )
	, DeltaRoll( SpeedRand( Rng ) )
	, DeltaPitch( SpeedRand( Rng ) )
	, DeltaYaw( SpeedRand( Rng ) )
	, DeltaPhi( OrbitRand( Rng ) )
	, DeltaTheta( OrbitRand( Rng ) )
	, DeltaChi( OrbitRand( Rng ) )
	, Chi( AngleRand( Rng ) )
	, Theta( AngleRand( Rng ) )
	, Phi( AngleRand( Rng ) )
{
	if( !StaticBindsInitailized() )
	{
		// clang-format off
		// Podstawa piêciok¹tna (le¿¹ca w p³aszczyŸnie XY, przy Z = -1.0f)
		std::vector<FVertex> Vertices = {
			{ 0.0f,  1.0f, -1.0f },  // Wierzcho³ek górny piêciok¹ta
			{ 0.951f,  0.309f, -1.0f },  // Prawy górny
			{ 0.588f, -0.809f, -1.0f },  // Prawy dolny
			{ -0.588f, -0.809f, -1.0f }, // Lewy dolny
			{ -0.951f,  0.309f, -1.0f }, // Lewy górny
			{ 0.0f, 0.0f, -1.0f },  // Œrodek podstawy
			
			// Wierzcho³ek wierzcho³kowy ostros³upa
			{ 0.0f, 0.0f, 1.0f } // Wierzcho³ek na górze ostros³upa
		};
		// clang-format on

		AddStaticBind( std::make_unique< BVertexBuffer >( Graphics, Vertices ) );

		std::unique_ptr< BVertexShader > VertexShader = std::make_unique< BVertexShader >( Graphics, L"Shader/Compiled/VertexShader.cso" );
		if( !VertexShader )
		{
			MX_EXCEPTION( "Failed to create Vertex shader in Pyramid!" );
		}

		ID3DBlob* const VertexShaderBlob = VertexShader->GetBytecode();
		AddStaticBind( std::move( VertexShader ) );

		AddStaticBind( std::make_unique< BPixelShader >( Graphics, L"Shader/Compiled/PixelShader.cso" ) );

		// clang-format off
		// Index buffer
		std::vector<unsigned short> const Indices = {
			 // Podstawa (piêciok¹t podzielony na trójk¹ty)
			 1, 5, 0,
			 2, 5, 1,
			 3, 5, 2,
			 4, 5, 3,
			 0, 5, 4,
			 
			 // Œciany boczne
			 0, 6, 1,
			 1, 6, 2,
			 2, 6, 3,
			 3, 6, 4,
			 4, 6, 0
		};
		// clang-format on

		AddStaticIndexBuffer( std::make_unique< BIndexBuffer >( Graphics, Indices ) );

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

		FConstantBufferFaceColor ConstantBufferFaceColor = { { { 0.95f, 0.75f, 0.85f }, { 0.75f, 0.95f, 0.75f }, { 0.65f, 0.85f, 1.0f }, { 1.0f, 0.85f, 0.65f },
			{ 0.85f, 0.65f, 1.0f }, { 0.78f, 0.88f, 0.95f } } };

		AddStaticBind( std::make_unique< BPixelConstantBuffer< FConstantBufferFaceColor > >( Graphics, ConstantBufferFaceColor ) );

		// clang-format off
		std::vector<D3D11_INPUT_ELEMENT_DESC> const InputElementDescription = { 
			{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		// clang-format on

		AddStaticBind( std::make_unique< BInputLayout >( Graphics, InputElementDescription, VertexShaderBlob ) );

		AddStaticBind( std::make_unique< BTopology >( Graphics, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );
	}
	else
	{
		SetIndexBufferFromStatics();
	}

	// Every box should have its own transform, rest should be static
	AddBind( std::make_unique< BTransformConstantBuffer >( Graphics, *this ) );
}

void DPyramid::Tick( float const DeltaTime )
{
	Roll += DeltaRoll * DeltaTime;
	Pitch += DeltaPitch * DeltaTime;
	Yaw += DeltaYaw * DeltaTime;
	Theta += DeltaTheta * DeltaTime;
	Phi += DeltaPhi * DeltaTime;
	Chi += DeltaChi * DeltaTime;
}

DirectX::XMMATRIX DPyramid::GetTransformMatrix() const
{
	return DirectX::XMMatrixRotationRollPitchYaw( Pitch, Yaw, Roll )  // Local rotation
		   * DirectX::XMMatrixTranslation( r, 0.0f, 0.0f )			  // Radius from center of the world
		   * DirectX::XMMatrixRotationRollPitchYaw( Theta, Phi, Chi ) // Orbital rotation around the center of the world
		   * DirectX::XMMatrixTranslation( 0.0f, 0.0f, 20.0f );
}
