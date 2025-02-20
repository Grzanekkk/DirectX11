// Copyright (c) 2024, Made by Jan Puto :>

#pragma once
#include "Drawable/Drawable.h"
#include "Bindable/Buffer/IndexBuffer.h"

template< typename T >
class DDrawableStaticBase : public DDrawable
{
public:
	bool StaticBindsInitailized()
	{
		// If first object added static bind for the class others don't have to do that
		return !StaticBinds.empty();
	}

	void AddStaticBind( std::unique_ptr< BBindable > Bind )
	{
		if( Bind )
		{
			assert( "Must use AddIndexBuffer to bind index buffer" && typeid( *bind ) != typeid( BIndexBuffer ) );

			StaticBinds.push_back( std::move( Bind ) );
		}
	}

	void AddStaticIndexBuffer( std::unique_ptr< BIndexBuffer > InIndexBuffer )
	{
		if( InIndexBuffer )
		{
			assert( "Index buffer is already added" && IndexBuffer == nullptr );

			IndexBuffer = InIndexBuffer.get();
			StaticBinds.push_back( std::move( InIndexBuffer ) );
		}
	}

	void SetIndexBufferFromStatics()
	{
		assert( "IndexBuffer is already set" && IndexBuffer == nullptr );

		for( auto& StaticBind : StaticBinds )
		{
			BIndexBuffer* IndexBufferCast = dynamic_cast< BIndexBuffer* >( StaticBind.get() );
			if( IndexBufferCast )
			{
				IndexBuffer = IndexBufferCast;
				return;
			}
		}

		assert( "Failed to find IndexBuffer in StaticBinds" && IndexBuffer != nullptr );
	}

	std::vector< std::unique_ptr< BBindable > > const& GetStaticBinds() const override
	{
		return StaticBinds;
	}

protected:
	static std::vector< std::unique_ptr< BBindable > > StaticBinds;
};

template< typename T >
std::vector< std::unique_ptr< BBindable > > DDrawableStaticBase< T >::StaticBinds;