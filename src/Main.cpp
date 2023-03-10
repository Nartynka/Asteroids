#include <SDL.h>
#include <SDL_image.h>
#include <cassert> 
#include <vector>

#include "Components/Components.h"
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

	//@TODO: Entity system/spawner needed to keep track of this
	// 
	//Player
	ComponentAllocator* comp_alloc = ComponentAllocator::Get();
	int player_mov_comp_idx = comp_alloc->CreateMovementComponent({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, {});
	comp_alloc->CreateTextureComponent("res/ship.png");

	//Asteroid
	comp_alloc->CreateMovementComponent({ 100, 200 }, { 0.1f, 0.1f });
	comp_alloc->CreateTextureComponent("res/asteroids/asteroid-1.png");

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
			//TODO: For now i need to pass 2 manually, otherwise it will iterate over all empty components and try to open empty textures
			render(renderer, comp_alloc->texture_components.data(), comp_alloc->movement_components.data(), 2);

			lastTime = (float)SDL_GetTicks();
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}