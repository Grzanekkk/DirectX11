// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Drawable/Drawable.h"
#include <random> 

class DBox : public DDrawable
{
public:
	DBox( MXGraphics& Graphics, std::mt19937& Rng, std::uniform_real_distribution< float >& AngleRand, std::uniform_real_distribution< float >& SpeedRand,
		std::uniform_real_distribution< float >& OrbitRand, std::uniform_real_distribution< float >& RadiusRand );
	DBox( DDrawable const& ) = delete;
	~DBox() = default;

	virtual void Tick( float const DeltaTime ) override;

	DirectX::XMMATRIX GetTransformMatrix() const override;

	/// SUPER WORK IN PROGRESS
	// position
	float r = 0.0f;
	float Roll = 0.0f;
	float Pitch = 0.0f;
	float Yaw = 0.0f;
	float Theta = 0.0f;
	float Phi = 0.0f;
	float Chi = 0.0f;

	// speed
	float DeltaRoll = 0.0f;
	float DeltaPitch = 0.0f;
	float DeltaYaw = 0.0f;
	float DeltaTheta = 0.0f;
	float DeltaPhi = 0.0f;
	float DeltaChi = 0.0f;
};