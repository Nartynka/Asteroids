#include "Systems.h"


// This here becouse SDL operates on degrees and movement on radians
// You would have to multipy both rotation in render system and angle in movement system
const int ROTATION_SPEED = 2;

//@TODO: This should iterate over InputComponents (not every input means movement - shooting, pausing etc)
void handle_input(MovementComponent* mov_components, size_t count)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	for (unsigned int i = 0; i < count; i++)
	{
		if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W])
		{
			mov_components[i].velocity.y = -1.0 * cos(mov_components[i].rotation * M_PI / 180.0);
			mov_components[i].velocity.x = sin(mov_components[i].rotation * M_PI / 180.0);
		}
		else if (currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S])
		{
			mov_components[i].velocity.y = 1.0 * cos(mov_components[i].rotation * M_PI / 180.0);
			mov_components[i].velocity.x = -sin(mov_components[i].rotation * M_PI / 180.0);
		}
		else
		{
			mov_components[i].velocity.y = 0.0;
			mov_components[i].velocity.x = 0.0;
		}

		if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A])
		{
			mov_components[i].rotation += -1.0 * ROTATION_SPEED;
		}
		else if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D])
		{
			mov_components[i].rotation += 1.0 * ROTATION_SPEED;
		}

		if (mov_components[i].rotation > 360)
			mov_components[i].rotation = 0;

	}

}