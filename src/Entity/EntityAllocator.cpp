#include "Entity/Entity.h"
#include <cstring>
#include <SDL_image.h>

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

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* path, Vec2& size)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* loaded_surface = IMG_Load(path);
	assert(loaded_surface != nullptr && "Unable to load image\n");

	new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	assert(new_texture != nullptr && "Unable to create texture from image\n");

	size = { (float)(loaded_surface->w), (float)loaded_surface->h };

	SDL_FreeSurface(loaded_surface);

	return new_texture;
}

int EntityAllocator::CreateEntity(Vec2 position, const char* path, SDL_Renderer* renderer, float radius, float rotation, bool is_rotating)
{
	unsigned int idx = (int)entities.size();

	size_t len = strlen(path) + 1;
	assert(len < 64 && "Path for texture longer than 64 characters");
	entities.push_back({ idx, position, rotation, is_rotating, radius });
	// loading texture must be here, because otherwise the size and texture were only loaded at render
	// and we need size for center of collision circle
	entities[idx].texture = load_texture(renderer, path, entities[idx].size);

	Vec2 center = { entities[idx].position.x + (entities[idx].size.x / 2), entities[idx].position.y + (entities[idx].size.y / 2) };
	entities[idx].center = center;

	// if we are loading texture here, is path to file still needed?
	strncpy_s(entities[idx].texture_path, path, len);

	return idx;
}

void EntityAllocator::DestroyEntity(int idx)
{
	ComponentAllocator* comp_aloc = ComponentAllocator::Get();
	comp_aloc->DestroyMovementComponent(entities[idx].comp_ids[Components::MOVEMENT_COMPONENT]);
	entities.erase(idx);
}
