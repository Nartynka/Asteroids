#include "Entity/Entity.h"
#include <cstring>


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

int EntityAllocator::CreateEntity(Vec2 position, const char* path, float rotation, bool is_rotating)
{
	unsigned int idx = (int)entities.size();

	size_t len = strlen(path) + 1;
	assert(len < 64 && "Path for texture longer than 64 characters");

	entities.push_back({ idx, position, rotation, is_rotating });
	strncpy_s(entities[idx].texture_path, path, len);

	return idx;
}

void EntityAllocator::DestroyEntity(int idx)
{
	ComponentAllocator* comp_aloc = ComponentAllocator::Get();
	comp_aloc->DestroyMovementComponent(entities[idx].comp_ids[Components::MOVEMENT_COMPONENT]);
	entities.erase(idx);
}
