#ifndef ENJON_PLAYER_CONTROLLER_SYSTEM_H
#define ENJON_PLAYER_CONTROLLER_SYSTEM_H

#include "ECS/Components.h"
#include "ECS/Entity.h"
#include "ECS/ComponentSystems.h"

#include <AI/SpatialHash.h>

#define	WALKPACE 	2.0f
#define SPRINTPACE 	WALKPACE * 6.0f

struct PlayerControllerSystem
{
	ECS::Systems::EntityManagerDeprecated* Manager;
	ECS::Component::PlayerController PlayerControllers[MAX_ENTITIES];
	std::vector<Enjon::uint32> Targets;  // Totally testing this for now...

	// Probably just make a targeting system and component for this data
	Enjon::uint32 CurrentIndex;
	Enjon::uint32 CurrentTarget;
	SpatialHash::Grid* Grid;
}; 

namespace ECS { namespace Systems { namespace PlayerController {

	// Constructs and returns new PlayerControllerSystem
	// TODO(John): Write custom allocator for this
	struct PlayerControllerSystem* NewPlayerControllerSystem(Systems::EntityManagerDeprecated* Manager);
	
	// Updates Controller of player it is attached to
	void Update(struct PlayerControllerSystem* System);	

	bool GetTargeting();
}}}


#endif

