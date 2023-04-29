#pragma once
#include "Components/Components.h"

void handle_input(int player_idx);

void move(float dt);

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
void render(struct SDL_Renderer* renderer);

extern int points;
void check_collision();