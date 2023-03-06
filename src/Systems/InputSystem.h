#pragma once
#include "Components/Components.h"

//@TODO: This should iterate over InputComponents (not every input means movement - shooting, pausing etc)
void handle_input(MovementComponent* mov_components, size_t count)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	for (unsigned int i = 0; i < count; i++)
	{
		if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W])
		{
			mov_components[i].velocity.y = -1.0;
		}
		else if (currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S])
		{
			mov_components[i].velocity.y = 1.0;
		}
		else 
		{
			mov_components[i].velocity.y = 0.0;
		}

		if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A])
		{
			mov_components[i].velocity.x = -1.0;
		}
		else if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D])
		{
			mov_components[i].velocity.x = 1.0;
		}
		else
		{
			mov_components[i].velocity.x = 0.0;
		}
	}
	
}