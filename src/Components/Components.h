#pragma once

#include "Vec2.h"
#include "HandleStaticVector.h"

enum Components
{
	MOVEMENT_COMPONENT,
	COUNT
};

constexpr int MAX_COMPONENT_COUNT = 16;
constexpr int MAX_ENTITY_COUNT = 16;

struct MovementComponent
{
	Vec2 velocity = {};
};

class ComponentAllocator
{
public:
	static ComponentAllocator* Get();

	int CreateMovementComponent(unsigned int idx, Vec2 velocity);

	void DestroyMovementComponent(int idx);

	HandleStaticVector<MovementComponent, MAX_COMPONENT_COUNT> movement_components;

private:
	~ComponentAllocator();
	static ComponentAllocator* allocator;
};