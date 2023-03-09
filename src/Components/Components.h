#pragma once

#include "Vec2.h"
#include "StaticVector.h"
#include <array>
#include <stack>

enum Components
{
	MOVEMENT_COMPONENT,
	RENDER_COMPONENT,
	COUNT
};

constexpr int MAX_COMPONENT_COUNT = 16;

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

class ComponentAllocator
{
public:
	static ComponentAllocator* Get();

	int CreateMovementComponent(Vec2 position, Vec2 velocity);
	int CreateTextureComponent(const char* path);

	void DestroyMovementComponent(int idx);
	void DestroyTextureComponent(int idx);

	//@TODO: These need to be replaced with a custom container (fixed vector)
	StaticVector<MovementComponent, MAX_COMPONENT_COUNT> movement_components;
	StaticVector<TextureComponent, MAX_COMPONENT_COUNT> texture_components;

private:
	ComponentAllocator();
	~ComponentAllocator();
	static ComponentAllocator* allocator;

	std::stack<int> movement_components_free_indeces;
	std::stack<int> texture_components_free_indeces;
};