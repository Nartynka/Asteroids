#pragma once
#include <SDL.h>
#include "Components/Components.h"

void handle_input(MovementComponent* mov_components, size_t count);

void move(MovementComponent* mov_components, size_t count, float dt);

void render(SDL_Renderer* renderer, TextureComponent* tex_components, MovementComponent* mov_components, size_t count);