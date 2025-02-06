// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Graphics/MXGraphics.h"
#include <DirectXMath.h>
#include <vector>
#include <memory>

class BBindable;
class BIndexBuffer;

class DDrawable
{
public:
	DDrawable() = default;
	DDrawable( DDrawable const& ) = delete;
	~DDrawable() = default;

	void Draw( MXGraphics& Graphics );
	virtual void Tick( float const DeltaTime ) = 0;
	void AddBind( std::unique_ptr< BBindable > Bind );
	void AddIndexBuffer( std::unique_ptr< BIndexBuffer > InIndexBuffer );

private:
	std::vector< std::unique_ptr< BBindable > > Binds;

	// Unique ptr of this is held in Binds, this is just for quick access
	BIndexBuffer const* IndexBuffer = nullptr;
};