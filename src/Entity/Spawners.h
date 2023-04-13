#pragma once
#include <Vec2.h>

struct SDL_Renderer;

int CreateAsteroid(Vec2 position, Vec2 velocity, float rotation, bool is_rotating, SDL_Renderer* renderer);
int CreatePlayer(Vec2 position, SDL_Renderer* renderer);
int CreateProjectile(Vec2 shooter_pos, Vec2 shooter_size, float shooter_rotation, SDL_Renderer* renderer);