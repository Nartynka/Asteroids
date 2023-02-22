#include <SDL.h>
#include <stdio.h>
#include <cassert> 

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

int main(int argc, char* args[])
{
	float dt = SDL_GetTicks();
	float lastTime = 0.f;
	float desiredDt = 1 / 60.f; // 60 FPS

	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0 && "SDL could not initialize!\n");

	window = SDL_CreateWindow("Does this work", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	assert(window != nullptr && "Window could not be created!\n");
	
	bool quit = false;
	SDL_Event event;
	//Game loop
	while (!quit)
	{
		dt = SDL_GetTicks() - lastTime;

		if (dt > desiredDt) 
		{
			// Handle input queue (1 = pending event; 0 = no event)
			while (SDL_PollEvent(&event) != 0)
			{
				//User requests quit / click X
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			screenSurface = SDL_GetWindowSurface(window);
			SDL_UpdateWindowSurface(window);

			lastTime = SDL_GetTicks();
		}
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}