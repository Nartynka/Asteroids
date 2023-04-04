#pragma once
#include <Vec2.h>

int CreateAsteroid(Vec2 position, Vec2 velocity, float rotation, bool is_rotating);
int CreatePlayer(Vec2 position);
int CreateProjectile(Vec2 shooter_pos, float shooter_rotation);