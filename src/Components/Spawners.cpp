#include "Spawners.h"
#include "Components.h"

static ComponentAllocator* comp_alloc = ComponentAllocator::Get();
static EntityAllocator* entity_alloc = EntityAllocator::Get();

int CreateAsteroid(Vec2 position, Vec2 velocity)
{
	int idx = entity_alloc->CreateEntity();
	comp_alloc->CreateMovementComponent(idx, position, velocity);
	comp_alloc->CreateTextureComponent(idx, "res/asteroids/asteroid-1.png");

	return idx;
}

int CreatePlayer(Vec2 position)
{
	int idx = entity_alloc->CreateEntity();

	comp_alloc->CreateMovementComponent(idx, position, { 0,0 });
	comp_alloc->CreateTextureComponent(idx, "res/ship.png");

	return idx;
}