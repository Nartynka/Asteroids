#include "Systems.h"
#include <SDL_image.h>
#include <cassert>
#include <Vec2.h>
#include <Entity/Entity.h>

void draw_circle(SDL_Renderer* renderer, Vec2 center, int radius)
{
	int x0 = (int)center.x;
	int y0 = (int)center.y;

	int x = radius - 1;
	int y = 0;
	int dx = 1;
	int dy = 1;
	int error = dx - (radius << 1);

	while (x >= y) {
		SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
		SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
		SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
		SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
		SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
		SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
		SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
		SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);

		if (error <= 0) {
			y++;
			error += dy;
			dy += 2;
		}
		if (error > 0) {
			x--;
			dx += 2;
			error += dx - (radius << 1);
		}
	}
}

void render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	EntityAllocator* entity_alloc = EntityAllocator::Get();
	ComponentAllocator* comp_alloc = ComponentAllocator::Get();

	for (unsigned int i = 0; i < entity_alloc->entities.size(); i++)
	{
		Entity& entity = entity_alloc->entities[i];

		SDL_Rect dest_rect = { (int)entity.position.x, (int)entity.position.y, (int)entity.size.x, (int)entity.size.y };
		SDL_RenderCopyEx(renderer, entity.texture, NULL, &dest_rect, entity.rotation, NULL, SDL_FLIP_NONE);

		// debug collision circles
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		draw_circle(renderer, entity.center, (int)entity.radius);
	}

	SDL_RenderPresent(renderer);
}
