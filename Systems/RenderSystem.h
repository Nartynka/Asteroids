#pragma once
#include <SDL.h>
#include "../Components/Components.h"

void render(SDL_Renderer* renderer, const TextureComponent& textureComp, const MovementComponent& moveComp)
{
	SDL_Rect a = { (int)moveComp.position.x, (int)moveComp.position.y, textureComp.size.w, textureComp.size.h };
	SDL_RenderCopy(renderer, textureComp.texture, NULL, &a);
}