#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>

#include "Entity/Entity.h"
#include "Entity/Spawners.h"
#include "Systems/Systems.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char* args[])
{
	//@TODO: This probably needs to be a struct of globally available FrameData resource or smth
	float dt = (float)(SDL_GetTicks() / 1000.f);
	float lastTime = 0.f;
	const float DESIRED_DT = 1 / 60.f; // 60 FPS

	srand(time(NULL));

	//@TODO: Initialization of SDL should be a part of some system initalization
	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0 && "SDL could not initialize!");

	window = SDL_CreateWindow("Does this work", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	assert(window != nullptr && "Window could not be created!");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	assert(renderer != nullptr && "Renderer could not be created!");

	result = IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG;
	assert(result && "SDL_image could not initialize!");

	result = TTF_Init();
	assert(result != -1 && "SDL_ttf could not initialize!");

	EntityAllocator* entity_alloc = EntityAllocator::Get();
	ComponentAllocator* comp_alloc = ComponentAllocator::Get();

	//Player
	int player_idx = CreatePlayer({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, renderer);

	// spawn asteroid ever 1 second
	float asteroidTimeout = 0.f;

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

				else if (!game_over && event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_SPACE)
					CreateProjectile(entity_alloc->entities[player_idx].position, entity_alloc->entities[player_idx].size, entity_alloc->entities[player_idx].rotation, renderer);
			}

			if (!game_over)
			{
				if (asteroidTimeout >= 1.f)
				{
					RandomAsteroid(renderer);
					asteroidTimeout = 0.f;
				}
				else
				{
					asteroidTimeout += dt;
				}

				handle_input(player_idx);
				move(dt);
				check_collision();
				entity_alloc->DestroyEntities();
			}
			
			// Points text
			queue_text_surface("Points: " + std::to_string(points));
			if(game_over)
			{
				queue_text_surface("GAME OVER!!");
			}
			
			render(renderer);

			lastTime = (float)SDL_GetTicks();
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}