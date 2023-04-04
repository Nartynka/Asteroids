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

int ComponentAllocator::CreateMovementComponent(unsigned int idx, Vec2 velocity)
{
	assert(movement_components.size() < MAX_COMPONENT_COUNT && "Maximum number of MovementComponents reached!");
	int mov_idx = movement_components.push_back({ velocity });

	EntityAllocator* entity_alloc = EntityAllocator::Get();
	entity_alloc->entities[idx].comp_ids[Components::MOVEMENT_COMPONENT] = mov_idx;

	return mov_idx;
}

void ComponentAllocator::DestroyMovementComponent(int idx)
{
	movement_components.erase(idx);
}