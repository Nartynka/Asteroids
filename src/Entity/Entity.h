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
};

class EntityAllocator
{
public:
	static EntityAllocator* Get();

	int CreateEntity(Vec2 position, const char* path, struct SDL_Renderer* renderer, float radius, float rotation = 0.f, bool is_rotating = false);
	void DestroyEntity(int idx);

	HandleStaticVector<Entity, MAX_ENTITY_COUNT> entities;
private:
	~EntityAllocator();
	static EntityAllocator* allocator;
};