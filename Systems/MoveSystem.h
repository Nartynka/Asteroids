#pragma once
#include "../Components/Components.h"

const int SPEED = 100;
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;


void move(MovementComponent& moveComp, float dt)
{
	moveComp.position += moveComp.velocity * SPEED * dt;
}

bool is_outside_screen(const MovementComponent& moveComp, const TextureComponent& sizeComp)
{
	if (moveComp.position.y < 0 || (moveComp.position.y + sizeComp.size.h > SCREEN_HEIGHT) || moveComp.position.x < 0 || (moveComp.position.x + sizeComp.size.w > SCREEN_WIDTH))
		return true;

	return false;
}
