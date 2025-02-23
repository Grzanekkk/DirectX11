// Copyright (c) 2024, Made by Jan Puto :>

#include "App/MXApp.h"
#include "Windows/MXWindow.h"
#include "Graphics/MXGraphics.h"
#include "Drawable/Shape/Box.h"
#include <random>
#include <iostream>

MXApp::MXApp()
	: WindowHandle{ WindowWidth, WindowHeight, "TOYOTA" }
{
	std::mt19937 rng( std::random_device{}() );
	std::uniform_real_distribution< float > AngleRand( 0.0f, 3.1415f * 2.0f );
	std::uniform_real_distribution< float > SpeedRand( 0.0f, 3.1415f * 2.0f );
	std::uniform_real_distribution< float > OrbitRand( 0.0f, 3.1415f * 0.3f );
	std::uniform_real_distribution< float > RadiusRand( 6.0f, 20.0f );
	for( auto i = 0; i < 60; i++ )
	{
		Boxes.push_back( std::make_unique< DBox >( WindowHandle.GetGraphics(), rng, AngleRand, SpeedRand, OrbitRand, RadiusRand ) );
		Pyramids.push_back( std::make_unique< DPyramid >( WindowHandle.GetGraphics(), rng, AngleRand, SpeedRand, OrbitRand, RadiusRand ) );
	}

	WindowHandle.GetGraphics().SetProjection( DirectX::XMMatrixPerspectiveLH( 1.0f, 3.0f / 4.0f, 0.5f, 40.0f ) );
	Clock = MXClock();
}

int MXApp::StartApp()
{
	Clock.StartClock();

	while( true )
	{
		if( std::optional< int > const EscapeCode = WindowHandle.ProcessMessages() )
		{
			return EscapeCode.value();
		}

		float const DeltaTime = Clock.GetDeltaTime();
		Clock.Tick();

		Tick( DeltaTime );
	}
}

void MXApp::Tick( float const DeltaTime )
{
	// TempTickCounter++;
	// if( TempTickCounter > 30 )
	//{
	//	TempTickCounter = 0;
	//	std::random_device rd;
	//	std::mt19937 gen( rd() );
	//	std::uniform_real_distribution< float > dis( 0.0, 1.0 );
	//	float const Red = dis( gen );
	//	float const Green = dis( gen );
	//	BackGroudColor = FColor( Red, Green, 1.f );
	// }

	// CurrentRotation += RotationSpeed;

	// float const TriangleX = WindowHandle.GetMouseHandle().GetPosX() / ( float ) WindowWidth * 2.f - 1.f;
	// float const TriangleY = -WindowHandle.GetMouseHandle().GetPosY() / ( float ) WindowHeight * 2.f + 1.f;

	// std::cout << "X:" << TriangleX << std::endl;
	// std::cout << "Y:" << TriangleY << std::endl;
	// WindowHandle.GetGraphics().ClearBuffer( BackGroudColor.R, BackGroudColor.G, BackGroudColor.G );
	// WindowHandle.GetGraphics().DrawTestTriangle( CurrentRotation, TriangleX, TriangleY * 2 );
	// WindowHandle.GetGraphics().DrawTestTriangle( -CurrentRotation + 66.f, 0.f, 0.f );
	// WindowHandle.GetGraphics().EndFrame();

	std::stringstream ss;
	float const Fps = 1.0f / DeltaTime;
	ss << "DeltaTime: " << DeltaTime << " FPS: " << Fps;
	WindowHandle.SetTitle( ss.str().c_str() );
	WindowHandle.GetGraphics().ClearBuffer( 0.07f, 0.0f, 0.12f );

	for( auto& Box : Boxes )
	{
		Box->Tick( DeltaTime );
		Box->Draw( WindowHandle.GetGraphics() );
	}

	for( auto& Pyramid : Pyramids )
	{
		Pyramid->Tick( DeltaTime );
		Pyramid->Draw( WindowHandle.GetGraphics() );
	}

	WindowHandle.GetGraphics().EndFrame();
}
