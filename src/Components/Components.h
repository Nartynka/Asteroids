#pragma once

#include "Vec2.h"
#include "HandleStaticVector.h"

enum Components
{
	MOVEMENT_COMPONENT,
	RENDER_COMPONENT,
	COUNT
};

constexpr int MAX_COMPONENT_COUNT = 16;
constexpr int MAX_ENTITY_COUNT = 16;

//@TODO : Split into TransformComponent and MovementComponent
struct MovementComponent
{
	Vec2 position = {};
	Vec2 velocity = {};
	float rotation = 0.f;
	bool is_rotating = false;
};

struct TextureComponent
{
	char texture_path[64];
	struct SDL_Texture* texture;
	Vec2 size = {};
	float tex_rotation = 0.f;
};

struct Entity
{
	unsigned int id;
	int comp_ids[Components::COUNT];
};

class ComponentAllocator
{
public:
	static ComponentAllocator* Get();

	int CreateMovementComponent(unsigned int idx, Vec2 position, Vec2 velocity, float rotation, bool is_rotating=false);
	int CreateTextureComponent(unsigned int idx, const char* path);

	void DestroyMovementComponent(int idx);
	void DestroyTextureComponent(int idx);

	HandleStaticVector<MovementComponent, MAX_COMPONENT_COUNT> movement_components;
	HandleStaticVector<TextureComponent, MAX_COMPONENT_COUNT> texture_components;

private:
	~ComponentAllocator();
	static ComponentAllocator* allocator;
};

class EntityAllocator
{
public:
	static EntityAllocator* Get();

	int CreateEntity();
	void DestroyEntity(int idx);

	HandleStaticVector<Entity, MAX_ENTITY_COUNT> entities;
private:
	~EntityAllocator();
	static EntityAllocator* allocator;
};