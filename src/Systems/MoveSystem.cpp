#include "Systems.h"

//@TODO: These don't belong here
const int SPEED = 100;
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

//@TODO: For now we can once again leave the screen
void move(MovementComponent* mov_components, size_t count, float dt)
{
	for (unsigned int i = 0; i < count; i++)
	{
		mov_components[i].position += mov_components[i].velocity * SPEED * dt;
	}
}
