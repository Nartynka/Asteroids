#include "Components.h"
#include <assert.h>

#include <SDL.h>
#include <SDL_image.h>

ComponentAllocator::ComponentAllocator()
{
	for (int i = MAX_COMPONENT_COUNT - 1; i >= 0; i--)
	{
		movement_components_free_indeces.push(i);
		texture_components_free_indeces.push(i);
	}
}

ComponentAllocator::~ComponentAllocator()
{
	delete ComponentAllocator::allocator;
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

int ComponentAllocator::CreateMovementComponent(Vec2 position, Vec2 velocity)
{
	assert(movement_components_free_indeces.size() > 0 && "Maximum number of MovementComponents reached!");

	int idx = movement_components_free_indeces.top();
	movement_components_free_indeces.pop();

	movement_components.insert(idx, { position, velocity });
	return idx;
}


int ComponentAllocator::CreateTextureComponent(const char* path)
{
	assert(texture_components_free_indeces.size() > 0 && "Maximum number of TextureComponents reached!");

	int idx = texture_components_free_indeces.top();
	texture_components_free_indeces.pop();

	texture_components.insert(idx, {});
	size_t len = strlen(path) + 1;
	assert(len < 64 && "Path for texture longer than 64 characters");
	strncpy_s(texture_components[idx].texture_path, path, len);

	return idx;
}

void ComponentAllocator::DestroyMovementComponent(int idx)
{
	movement_components.erase(idx);
	movement_components_free_indeces.push(idx);
}

void ComponentAllocator::DestroyTextureComponent(int idx)
{
	texture_components.erase(idx);
	texture_components_free_indeces.push(idx);
}