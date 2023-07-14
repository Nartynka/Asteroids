#pragma once
#include "Components/Components.h"
#include "Vec2.h"

struct Entity
{
	unsigned int id;

	// transform
	Vec2 position = {};
	float rotation = 0.f;
	bool is_rotating = false;

	// physics/collision
	float radius = 0;
	Vec2 center = {};

	// visuals
	char texture_path[64];
	struct SDL_Texture* texture;
	Vec2 size = {};

	int comp_ids[Components::COUNT];

	bool HasComponent(Components comp_id) {
		return comp_ids[comp_id] != -1;
	}
};

class EntityAllocator
{
public:
	static EntityAllocator* Get();

	int CreateEntity(Vec2 position, const char* path, struct SDL_Renderer* renderer, float radius, float rotation = 0.f, bool is_rotating = false);

	void QueueDestroy(int entity_id);
	void DestroyEntities();

	HandleStaticVector<Entity, MAX_ENTITY_COUNT> entities;
private:
	~EntityAllocator();
	static EntityAllocator* allocator;
	StaticVector<int, MAX_ENTITY_COUNT> queued_entities;
};