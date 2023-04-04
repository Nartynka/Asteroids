#include "Systems.h"
#include <SDL.h>
#include <Components/Components.h>
#include "Entity/Entity.h"

// This here becouse SDL operates on degrees and movement on radians
// You would have to multipy both rotation in render system and angle in movement system
const int ROTATION_SPEED = 2;

//@TODO: This should iterate over InputComponents (not every input means movement - shooting, pausing etc)
void handle_input(int player_idx)
{
	EntityAllocator* entity_alloc = EntityAllocator::Get();
	Entity& player = entity_alloc->entities[player_idx];

	ComponentAllocator* comp_alloc = ComponentAllocator::Get();
	MovementComponent& player_movement = comp_alloc->movement_components[player.comp_ids[Components::MOVEMENT_COMPONENT]];

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W])
	{
		player_movement.velocity.y = -1.0 * cos(player.rotation * M_PI / 180.0);
		player_movement.velocity.x = sin(player.rotation * M_PI / 180.0);
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S])
	{
		player_movement.velocity.y = 1.0 * cos(player.rotation * M_PI / 180.0);
		player_movement.velocity.x = -sin(player.rotation * M_PI / 180.0);
	}
	else
	{
		player_movement.velocity.y = 0.0;
		player_movement.velocity.x = 0.0;
	}

	if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A])
	{
		player.rotation += -1.0 * ROTATION_SPEED;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D])
	{
		player.rotation += 1.0 * ROTATION_SPEED;
	}

	if (player.rotation > 360)
		player.rotation = 0;
}