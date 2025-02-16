// Copyright (c) 2024, Made by Jan Puto :>

#include "Drawable/Drawable.h"
#include "Bindable/Bindable.h"
#include "Exceptions/MXException.h"
#include "Bindable/Buffer/IndexBuffer.h"

void DDrawable::Draw( MXGraphics& Graphics )
{
	for( auto& Bindable : Binds )
	{
		if( Bindable )
		{
			Bindable->Bind( Graphics );
		}
		else
		{
			MX_EXCEPTION( "Invalid Bindable found!" );
		}
	}

	// Draw call
	if( IndexBuffer )
	{
		Graphics.DrawIndexed( IndexBuffer->GetCount() );
	}
	else
	{
		MX_EXCEPTION( "Failed to issue a Draw Call! Valid index buffer is required." );
	}
}

void DDrawable::AddBind( std::unique_ptr< BBindable > Bind )
{
	if( Bind )
	{
		assert( "Must use AddIndexBuffer to bind index buffer" && typeid( *bind ) != typeid( IndexBuffer ) );

		Binds.push_back( std::move( Bind ) );
	}
}

void DDrawable::AddIndexBuffer( std::unique_ptr< BIndexBuffer > InIndexBuffer )
{
	assert( "Index buffer is already added" && IndexBuffer == nullptr );

	IndexBuffer = InIndexBuffer.get();
	Binds.push_back( std::move( InIndexBuffer ) );
}