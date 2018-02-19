#include "Entity/Component.h"
#include "Entity/Entity.h"
#include "Entity/EntityManager.h"

namespace Enjon 
{ 
	
	//=========================================================================

	ComponentArray::ComponentArray( )
	{ 
	}
	
	//=========================================================================

	ComponentArray::~ComponentArray( )
	{
		mComponentMap.clear( );
		mComponentPtrs.clear( );
	}

	//=========================================================================

	Entity* Component::GetEntity() const
	{
		return mEntity;
	}
	
	//=========================================================================

	void Component::SetEntity( Entity* entity )
	{
		mEntity = entity;
	}
	
	//=========================================================================

	void Component::SetID( u32 id )
	{
		mComponentID = id;
	}
	
	//=========================================================================

	void Component::SetBase( ComponentWrapperBase* base )
	{
		mBase = base;
	} 
	
	//=========================================================================

	void Component::PostConstruction( )
	{ 
		// Nothing by default...
	}
	
	//=========================================================================

	void Component::Initialize( )
	{ 
		// Nothing by default...
	}
	
	//=========================================================================

	void Component::Start( )
	{ 
		// Nothing by default...
	}
	
	//=========================================================================

	void Component::Update( )
	{ 
		// Nothing by default...
	} 
	
	//=========================================================================

	void Component::Shutdown( )
	{ 
		// Nothing by default
	}
	
	//=========================================================================

	void ComponentArray::RemoveComponent( const u32& entityId )
	{
		if ( HasEntity( entityId ) )
		{
			auto cPtrList = &mComponentPtrs;
			auto cMap = &mComponentMap;

			// Get component
			auto compPtr = mComponentMap[entityId];

			// Remove ptr from point list map
			cPtrList->erase( std::remove( cPtrList->begin( ), cPtrList->end( ), compPtr ), cPtrList->end( ) );

			// Finally remove from map
			cMap->erase( entityId );

			// Set component's base to nullptr
			compPtr->mBase = nullptr;
		}
	} 
	
	//=========================================================================

	void Component::UpdateTransform( const Transform& transform )
	{
		// Nothing by default...
	}
	
	//=========================================================================
}
