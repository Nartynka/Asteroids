#include "Components.h"
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

int ComponentAllocator::CreateMovementComponent(unsigned int idx, Vec2 position, Vec2 velocity)
{
	assert(movement_components.size() < MAX_COMPONENT_COUNT && "Maximum number of MovementComponents reached!");
	int mov_idx = movement_components.push_back({ position, velocity });

	EntityAllocator* entity_alloc = EntityAllocator::Get();
	entity_alloc->entities[idx].comp_ids[Components::MOVEMENT_COMPONENT] = mov_idx;

	return mov_idx;
}


int ComponentAllocator::CreateTextureComponent(unsigned int idx, const char* path)
{
	assert(texture_components.size() < MAX_COMPONENT_COUNT && "Maximum number of TextureComponents reached!");

	int tex_idx = texture_components.push_back({});
	size_t len = strlen(path) + 1;
	assert(len < 64 && "Path for texture longer than 64 characters");
	strncpy_s(texture_components[idx].texture_path, path, len);

	EntityAllocator* entity_alloc = EntityAllocator::Get();
	entity_alloc->entities[idx].comp_ids[Components::RENDER_COMPONENT] = tex_idx;

	return tex_idx;
}

void ComponentAllocator::DestroyMovementComponent(int idx)
{
	movement_components.erase(idx);
}

void ComponentAllocator::DestroyTextureComponent(int idx)
{
	texture_components.erase(idx);
}