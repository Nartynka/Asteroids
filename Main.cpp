#include <SDL.h>
#include <stdio.h>

//Screen size
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Images to display
	SDL_Surface* background = NULL;
	SDL_Surface* blob = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("Does this work", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);
			// load images to display
			background = SDL_LoadBMP("background.bmp");
			blob = SDL_LoadBMP("blob.bmp");
			if (background == NULL || blob == NULL)
			{
				printf("Unable to load image, SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				bool quit = false;
				SDL_Event event;

				// Start position of blob at the center of the window
				int blobpos_x = SCREEN_WIDTH / 2 - 112 / 2;
				int blobpos_y = SCREEN_HEIGHT / 2 - 112 / 2;

				//Game loop
				while (!quit)
				{
					// Handle input queue (1 = pending event; 0 = no event)
					while (SDL_PollEvent(&event) != 0)
					{
						//User requests quit / click X
						if (event.type == SDL_QUIT)
						{
							quit = true;
						}
						// if key is pressed then modify blob position accordingly
						else if (event.type == SDL_KEYDOWN)
						{
							SDL_Keycode key = event.key.keysym.sym;

							if (key == SDLK_UP || key == SDLK_w)
								blobpos_y -= 10;
							if (key == SDLK_DOWN || key == SDLK_s)
								blobpos_y += 10;
							if (key == SDLK_LEFT || key == SDLK_a)
								blobpos_x -= 10;
							if (key == SDLK_RIGHT || key == SDLK_d)
								blobpos_x += 10;
						}
					}
					// draw background
					SDL_BlitSurface(background, NULL, screenSurface, NULL);

					//if (blobpos_y > SCREEN_HEIGHT || blobpos_y < 0 || blobpos_x > SCREEN_WIDTH || blobpos_x < 0)

					// set blob position
					SDL_Rect spritePosition;
					spritePosition.x = blobpos_x;
					spritePosition.y = blobpos_y;
					// draw blob
					SDL_BlitSurface(blob, NULL, screenSurface, &spritePosition);

					//Update the surface
					SDL_UpdateWindowSurface(window);
				}
			}
		}
	}

	// free surfaces
	SDL_FreeSurface(background);
	background = NULL;
	SDL_FreeSurface(blob);
	blob = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	//Quit SDL subsystems
	SDL_Quit();
	int i;
	scanf_s("%d", &i);
	return 0;
}
