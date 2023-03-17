#pragma once

#include "Vec2.h"
#include "StaticVector.h"

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
};

struct TextureComponent
{
	char texture_path[64];
	struct SDL_Texture* texture;
	Vec2 size = {};
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

	int CreateMovementComponent(unsigned int idx, Vec2 position, Vec2 velocity);
	int CreateTextureComponent(unsigned int idx, const char* path);

	void DestroyMovementComponent(int idx);
	void DestroyTextureComponent(int idx);

	StaticVector<MovementComponent, MAX_COMPONENT_COUNT> movement_components;
	StaticVector<TextureComponent, MAX_COMPONENT_COUNT> texture_components;

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

	StaticVector<Entity, MAX_ENTITY_COUNT> entities;
private:
	~EntityAllocator();
	static EntityAllocator* allocator;
};