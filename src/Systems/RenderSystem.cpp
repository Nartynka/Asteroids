#include "Systems.h"
#include <Vec2.h>
#include <Entity/Entity.h>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <cassert>

StaticVector<SDL_Surface*, 16> queued_text_surfaces;

#ifdef _DEBUG
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
#endif

void queue_text_surface(std::string&& text)
{
	TTF_Font* font = TTF_OpenFont("res/fonts/PressStart.ttf", 24);
	assert(font != nullptr && "Failed to load font!");

	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});

	assert(text_surface != NULL && "Unable to render text surface!");

	queued_text_surfaces.push_back(text_surface);
}

void render_text(SDL_Renderer* renderer)
{
	for (int i = (int)queued_text_surfaces.size()-1; i >= 0; i--)
	{
		SDL_Surface* text_surface = queued_text_surfaces[i];
		assert(text_surface != NULL && "Unable to render text surface!");

		SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		assert(text_texture != NULL && "Unable to create texture from rendered text!");

		SDL_Rect text_dsrect = { (SCREEN_WIDTH / 2) - (text_surface->w / 2), 20+(text_surface->h+24)*i, text_surface->w, text_surface->h };
		SDL_FreeSurface(text_surface);
		queued_text_surfaces.erase(i);
		SDL_RenderCopy(renderer, text_texture, NULL, &text_dsrect);
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
		Entity& entity = entity_alloc->entities.data()[i];

		SDL_Rect dest_rect = { (int)entity.position.x, (int)entity.position.y, (int)entity.size.x, (int)entity.size.y };
		SDL_RenderCopyEx(renderer, entity.texture, NULL, &dest_rect, entity.rotation, NULL, SDL_FLIP_NONE);

#ifdef _DEBUG
		// debug collision circles
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		draw_circle(renderer, entity.center, (int)entity.radius);
#endif
	}

	render_text(renderer);
	SDL_RenderPresent(renderer);
}