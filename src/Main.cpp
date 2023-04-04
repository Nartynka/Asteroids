#include <SDL.h>
#include <SDL_image.h>

#include "Components/Components.h"
#include "Entity/Entity.h"

#include "Entity/Spawners.h"
#include "Systems/Systems.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	//@TODO: This probably needs to be a struct of globally available FrameData resource or smth
	float dt = (float)(SDL_GetTicks() / 1000.f);
	float lastTime = 0.f;
	const float DESIRED_DT = 1 / 60.f; // 60 FPS

	//@TODO: Initialization of SDL should be a part of some system initalization
	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0 && "SDL could not initialize!");

	window = SDL_CreateWindow("Does this work", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	assert(window != nullptr && "Window could not be created!");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	assert(renderer != nullptr && "Renderer could not be created!");

	result = IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG;
	assert(result && "SDL_image could not initialize!");

	EntityAllocator* entity_alloc = EntityAllocator::Get();

	//Player
	int player_idx = CreatePlayer({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });

	//Asteroid
	CreateAsteroid({ 100, 200 }, { 0.1f, 0.2f }, 70.f, true);
	bool quit = false;
	SDL_Event event;

	//Game loop
	while (!quit)
	{
		dt = (SDL_GetTicks() - lastTime) / 1000;

		if (dt >= DESIRED_DT)
		{
			//@TODO: This probably belongs inside input handling system
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
					quit = true;
				if (event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_SPACE)
					CreateProjectile(entity_alloc->entities[player_idx].position, entity_alloc->entities[player_idx].rotation);
			}

			//TODO: Manually providing player's MovComp. Once it operates on InputComponents, will no longer be necessary
			handle_input(player_idx);
			move(dt);
			render(renderer, entity_alloc->entities.size());

			lastTime = (float)SDL_GetTicks();
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}