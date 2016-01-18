#ifndef RENDERER2DSYSTEM_H
#define RENDERER2DSYSTEM_H

#include "ECS/Components.h"
#include "ECS/Entity.h"
#include "ECS/ComponentSystems.h"

struct Renderer2DSystem
{
	ECS::Systems::EntityManager* Manager;
	ECS::Component::Renderer2DComponent Renderers[MAX_ENTITIES];
};

namespace ECS { namespace Systems { namespace Renderer2D {

	// Updates Renderers of EntityManager
	void Update(struct EntityManager* Manager);

	// Create new Render2DSystem
	Renderer2DSystem* NewRenderer2DSystem(struct EntityManager* Manager);	
}}}


#endif
