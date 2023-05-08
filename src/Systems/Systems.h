#pragma once
#include "Components/Components.h"
#include <string>

void handle_input(int player_idx);

void move(float dt);

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
void render(struct SDL_Renderer* renderer);

void queue_text_surface(std::string&& text);

extern int points;
extern bool game_over;
void check_collision();