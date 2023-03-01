#pragma once
#include <SDL_image.h>

struct Vec2
{
	union
	{
		float x;
		float w;
	};

	union
	{
		float y;
		float h;
	};
	void operator+=(Vec2 b) {
		x += b.x;
		y += b.y;
	}
	void operator-=(Vec2 b) {
		x -= b.x;
		y -= b.y;
	}
	Vec2 operator*(float b) {
		Vec2 temp = { x, y };
		temp.x *= b;
		temp.y *= b;
		return temp;
	}
};

struct Size2
{
	int w, h;
};

struct TextureComponent
{
	int id;
	SDL_Texture* texture;
	Vec2 size;
};

struct MovementComponent
{
	int id;
	Vec2 velocity = { 0,0 };
	Vec2 position = { 0,0 };
};
