#pragma once
#include "Components/Components.h"

void handle_input(MovementComponent& moveComp)
{
	moveComp.velocity = { 0,0 };
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W])
	{
		moveComp.velocity.y = -1.0;
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S])
	{
		moveComp.velocity.y = 1.0;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A])
	{
		moveComp.velocity.x = -1.0;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D])
	{
		moveComp.velocity.x = 1.0;
	}
}