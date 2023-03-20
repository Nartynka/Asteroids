#include "Components.h"

EntityAllocator::~EntityAllocator()
{
	delete allocator;
}

EntityAllocator* EntityAllocator::allocator = nullptr;

EntityAllocator* EntityAllocator::Get()
{
	if (!allocator)
	{
		allocator = new EntityAllocator();
	}

	return allocator;
}

int EntityAllocator::CreateEntity()
{
	unsigned int idx = (int)entities.size();
	return entities.push_back({ idx });
}

void EntityAllocator::DestroyEntity(int idx)
{
	ComponentAllocator* comp_aloc = ComponentAllocator::Get();
	comp_aloc->DestroyMovementComponent(entities[idx].comp_ids[Components::MOVEMENT_COMPONENT]);
	comp_aloc->DestroyTextureComponent(entities[idx].comp_ids[Components::RENDER_COMPONENT]);
	entities.erase(idx);
}
