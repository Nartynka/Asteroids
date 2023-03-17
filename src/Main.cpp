#include <SDL.h>
#include <SDL_image.h>
#include <cassert> 
#include <vector>

#include "Components/Components.h"
#include "Components/Spawners.h"

#include "Systems/InputSystem.cpp"
#include "Systems/MoveSystem.cpp"
#include "Systems/RenderSystem.cpp"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

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

	ComponentAllocator* comp_alloc = ComponentAllocator::Get();
	EntityAllocator* entity_alloc = EntityAllocator::Get();

	//Player
	int player_idx = CreatePlayer({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
	int player_mov_comp_idx = entity_alloc->entities[player_idx].comp_ids[Components::MOVEMENT_COMPONENT];

	//Asteroid
	CreateAsteroid({ 100, 200 }, { 0.1f, 0.1f });

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
			}

			//TODO: Manually providing player's MovComp. Once it operates on InputComponents, will no longer be necessary
			handle_input(&comp_alloc->movement_components[player_mov_comp_idx], 1);
			move(comp_alloc->movement_components.data(), comp_alloc->movement_components.size(), dt);
			render(renderer, comp_alloc->texture_components.data(), comp_alloc->movement_components.data(), comp_alloc->movement_components.size());

			lastTime = (float)SDL_GetTicks();
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}