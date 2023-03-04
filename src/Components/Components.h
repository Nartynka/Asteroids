#pragma once

#include "Vec2.h"

enum Components
{
	MOVEMENT_COMPONENT,
	RENDER_COMPONENT,
	COUNT
};

constexpr int MAX_COMPONENT_COUNT = 128;

struct TextureComponent
{
	SDL_Texture* texture;
	Vec2 size = {};
};

struct MovementComponent
{
	Vec2 velocity = {};
	Vec2 position = {};
};