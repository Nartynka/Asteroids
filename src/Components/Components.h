#pragma once

#include "Vec2.h"
#include "HandleStaticVector.h"

enum Components
{
	MOVEMENT_COMPONENT,
	PLAYER,
	ASTEROID,
	BULLET,
	COUNT
};

constexpr int MAX_COMPONENT_COUNT = 64;
constexpr int MAX_ENTITY_COUNT = 64;

struct MovementComponent
{
	Vec2 velocity = {};
};

class ComponentAllocator
{
public:
	static ComponentAllocator* Get();

	int CreateMovementComponent(int entity_id, Vec2 velocity);
	void DestroyMovementComponent(int entity_id);

	HandleStaticVector<MovementComponent, MAX_COMPONENT_COUNT> movement_components;

	int CreatePlayerComponent(int entity_id);
	int CreateAsteroidComponent(int entity_id);
	int CreateBulletComponent(int entity_id);

	void DestroyPlayerComponent(int entity_id);
	void DestroyAsteroidComponent(int entity_id);
	void DestroyBulletComponent(int entity_id);

private:
	~ComponentAllocator();
	static ComponentAllocator* allocator;
};