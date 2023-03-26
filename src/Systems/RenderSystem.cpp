#include "Systems.h"
#include <SDL_image.h>

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* path, Vec2& size)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* loaded_surface = IMG_Load(path);
	assert(loaded_surface != nullptr && "Unable to load image\n");

	new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	assert(new_texture != nullptr && "Unable to create texture from image\n");

	size = { (float)(loaded_surface->w), (float)loaded_surface->h };

	SDL_FreeSurface(loaded_surface);

	return new_texture;
}

//@TODO: Multiple problems here:
// TextureComponents and MovementComponents are separate arrays, every loop will be two cache misses
// There is no guarantee that the same index will be for both Movement and Texture Components
void render(SDL_Renderer* renderer, TextureComponent* tex_components, MovementComponent* mov_components, size_t count)
{
	SDL_RenderClear(renderer);

	for (unsigned int i = 0; i < count; i++)
	{
		TextureComponent* tex = &tex_components[i];
		MovementComponent* mov = &mov_components[i];

		//@TODO: No if's in tight loops. This should be properly handled by resource management of some sorts
		// Also it's not rendering system's responsibility to load resources
		if (!tex->texture)
		{
			tex->texture = load_texture(renderer, tex->texture_path, tex->size);
		}

		SDL_Rect dest_rect = { (int)mov->position.x, (int)mov->position.y, (int)tex->size.x, (int)tex->size.y };
		SDL_RenderCopyEx(renderer, tex->texture, NULL, &dest_rect, mov_components[i].rotation, NULL, SDL_FLIP_NONE);
	}

	SDL_RenderPresent(renderer);
}

