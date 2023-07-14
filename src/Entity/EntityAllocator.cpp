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
	size_t len = strlen(path) + 1;
	assert(len < 64 && "Path for texture longer than 64 characters");
	
	unsigned int idx = entities.push_back({});

	Entity& entity = entities[idx];

	entity = { idx, position, rotation, is_rotating, radius };
	// loading texture must be here, because otherwise the size and texture were only loaded at render
	// and we need size for center of collision circle
	entity.texture = load_texture(renderer, path, entity.size);

	Vec2 center = { entity.position.x + (entity.size.x / 2), entity.position.y + (entity.size.y / 2) };
	entity.center = center;

	// if we are loading texture here, is path to file still needed?
	strncpy_s(entity.texture_path, path, len);

	for (int i = 0; i < Components::COUNT; i++)
	{
		entity.comp_ids[i] = -1;
	}

	return idx;
}

void EntityAllocator::QueueDestroy(int entity_id)
{
	queued_entities.push_back(entity_id);
}

void EntityAllocator::DestroyEntities()
{
	if (queued_entities.size() > 0)
	{
		ComponentAllocator* comp_aloc = ComponentAllocator::Get();

		for (int i = 0; i < queued_entities.size(); i++)
		{
			int entity_id = queued_entities[i];
			comp_aloc->DestroyMovementComponent(entity_id);
			entities.erase(entity_id);
		}

		for (int i = queued_entities.size()-1; i >= 0; i--)
		{
			queued_entities.erase(i);
		}
	}
}
