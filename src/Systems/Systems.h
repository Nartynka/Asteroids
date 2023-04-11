#pragma once
#include "Components/Components.h"

void handle_input(int player_idx);

void move(float dt);

void render(struct SDL_Renderer* renderer);

bool check_collision();