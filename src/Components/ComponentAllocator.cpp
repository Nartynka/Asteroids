#include "Components.h"
#include "Entity/Entity.h"
#include <assert.h>
#include <cstring>

ComponentAllocator::~ComponentAllocator()
{
	delete allocator;
}

ComponentAllocator* ComponentAllocator::allocator = nullptr;

ComponentAllocator* ComponentAllocator::Get()
{
	if (allocator)
	{
		return allocator;
	}

	allocator = new ComponentAllocator();
	return allocator;
}

int ComponentAllocator::CreateMovementComponent(int entity_id, Vec2 velocity)
{
	assert(movement_components.size() < MAX_COMPONENT_COUNT && "Maximum number of MovementComponents reached!");
	int mov_idx = movement_components.push_back({ velocity });

	EntityAllocator* entity_alloc = EntityAllocator::Get();
	entity_alloc->entities[entity_id].comp_ids[Components::MOVEMENT_COMPONENT] = mov_idx;

	return mov_idx;
}

void ComponentAllocator::DestroyMovementComponent(int entity_id)
{
	EntityAllocator* entity_alloc = EntityAllocator::Get();
	Entity& entity = entity_alloc->entities[entity_id];
	movement_components.erase(entity.comp_ids[Components::MOVEMENT_COMPONENT]);
	entity.comp_ids[Components::MOVEMENT_COMPONENT] = -1;
}

int ComponentAllocator::CreatePlayerComponent(int entity_id)
{
	EntityAllocator* entity_alloc = EntityAllocator::Get();
	entity_alloc->entities[entity_id].comp_ids[Components::PLAYER] = 1;

	return 1;
}

int ComponentAllocator::CreateAsteroidComponent(int entity_id)
{
	EntityAllocator* entity_alloc = EntityAllocator::Get();
	entity_alloc->entities[entity_id].comp_ids[Components::ASTEROID] = 1;

	return 1;
}

int ComponentAllocator::CreateBulletComponent(int entity_id)
{
	EntityAllocator* entity_alloc = EntityAllocator::Get();
	entity_alloc->entities[entity_id].comp_ids[Components::BULLET] = 1;

	return 1;
}

void ComponentAllocator::DestroyPlayerComponent(int entity_id)
{
	EntityAllocator* entity_alloc = EntityAllocator::Get();
	entity_alloc->entities[entity_id].comp_ids[Components::PLAYER] = -1;
}

void ComponentAllocator::DestroyAsteroidComponent(int entity_id)
{
	EntityAllocator* entity_alloc = EntityAllocator::Get();
	entity_alloc->entities[entity_id].comp_ids[Components::ASTEROID] = -1;
}

void ComponentAllocator::DestroyBulletComponent(int entity_id)
{
	EntityAllocator* entity_alloc = EntityAllocator::Get();
	entity_alloc->entities[entity_id].comp_ids[Components::BULLET] = -1;
}
