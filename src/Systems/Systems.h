#pragma once
#include <SDL_image.h>

void handle_input(int player_idx);

void move(float dt);

void render(SDL_Renderer* renderer, size_t count);