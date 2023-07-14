#pragma once

struct Vec2
{
	float x, y;
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
