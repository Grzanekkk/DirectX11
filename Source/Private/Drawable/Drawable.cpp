// Copyright (c) 2024, Made by Jan Puto :>

#include "Drawable/Drawable.h"
#include "Bindable/Bindable.h"

void DDrawable::Draw( MXGraphics& Graphics )
{
	for( std::unique_ptr< BBindable >& Bindable : Binds )
	{
		Bindable->Bind( Graphics );
	}

	// Draw call
}

void DDrawable::AddBind( std::unique_ptr< BBindable > Bind )
{
	// DO CHECKS
	Binds.push_back( std::move( Bind ) );
}
