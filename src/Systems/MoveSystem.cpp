#include "Systems.h"
#include <stdio.h>

//@TODO: These don't belong here
const int SPEED = 300;
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

//@TODO: For now we can once again leave the screen
void move(MovementComponent* mov_components, size_t count, float dt)
{
	for (unsigned int i = 0; i < count; i++)
	{
		mov_components[i].position.x += mov_components[i].velocity.x * SPEED * dt;
		mov_components[i].position.y += mov_components[i].velocity.y * SPEED * dt;

		if(mov_components[i].is_rotating)
			mov_components[i].rotation += dt * 100;
	}
}
