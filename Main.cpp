#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>

//Screen size
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

SDL_Texture* load_texture(std::string path);
bool check_collision(SDL_Rect a, SDL_Rect b);
//The window we'll be rendering to
SDL_Window* window = NULL;
//The surface contained by the window
SDL_Surface* screenSurface = NULL;
// Renderer for rendering images
SDL_Renderer* renderer = NULL;

int main(int argc, char* args[])
{
	//Images to display
	//SDL_Surface* background = NULL;
	//SDL_Surface* blob = NULL;
	//SDL_Surface* blob_png = NULL;
	SDL_Rect sprite;
	// 988 x 704
	sprite.h = 70;
	sprite.w = 98;
	SDL_Rect enemy = { 100, 100, 200, 200 };
	SDL_Color color = { 255, 100, 50 };
	SDL_Texture* help_texture = NULL;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("Does this work", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if(!window)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			/*
			// Nie wiem czy to usun¹æ czy zostawiæ
			//Uint32 flags = SDL_GetWindowFlags(window);
			//if (flags & SDL_WINDOW_SHOWN)
			//	printf("ustawione show");
			// 
			// SDL_WINDOW_SHOWN = 4 (0100)
			// 
			//	 0010 0010 0100 
			// & 0000 0000 0100
			//	 0000 0000 0100 == true (flaga *jest* ustawiona)
			//	 ----------------------------
			//	 !Ka¿da liczba która nie jest zerem jest true!
			//	 0000 0000 0100 == true
			//	 0000 0000 0000 == false
			// 	 ----------------------------
			//
			//if (flags & SDL_WINDOW_BORDERLESS)
				//printf("ustawione borderless");
			// 
			// SDL_WINDOW_BORDERLESS = 16 (0001 0000)
			// 
			//	 0010 0010 0100 
			// & 0000 0001 0000
			//	 0000 0000 0000 == false (flaga *nie jest* ustawiona)
			//	 ----------------------------

			//if ((flags & (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)) == (SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS))
			//	printf("ustawione shown i borderless");

			// SDL_WINDOW_SHOWN = 4 (0100)
			// SDL_WINDOW_BORDERLESS = 16 (0001 0000)

			//   0000 0000 0100 // SDL_WINDOW_SHOWN
			// | 0000 0001 0000 // SDL_WINDOW_BORDERLESS
			//	 0000 0001 0100 // SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS

			//	 0010 0010 0100
			// & 0000 0001 0100
			//	 0000 0000 0100 != 0000 0001 0100
			//	 window nie ma obu flag
			*/
			// Create renderer
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer == NULL) 
			{
				printf("Unable to create renderer! SDL Error: %s\n", SDL_GetError());
			}

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}

			// load images to display
			//background = SDL_LoadBMP("background.bmp");
			//blob = SDL_LoadBMP("blob.bmp");

			// most of bitmaps are 24-bit and most of modern displays are not 
			// If we blit an image that's 24bit onto a 32bit image, SDL will convert it every single time the image is blitted
			//background = SDL_ConvertSurface(background, screenSurface->format, 0);
			//blob = SDL_ConvertSurface(blob, screenSurface->format, 0);
			//blob_texture = SDL_CreateTextureFromSurface(renderer, blob_png);
			//SDL_FreeSurface(blob_png);

			/*
			Texture vs Surface
			Surface - software rendering (cpu), stored in RAM, slower, you have direct acces to image
			Texture - hardware rendering (gpu), stored in VRAM, much faster, you don't have direct acces to image (OpenGL/DirectX)
			*/

			SDL_Texture* blob_texture = load_texture("blob.png");
			SDL_Texture* frog_texture = load_texture("frog.png");
			help_texture = blob_texture;
			SDL_Texture* background = load_texture("background.jpg");

			bool quit = false;
			SDL_Event event;

			// Start position of blob at the center of the window
			int blobpos_x = SCREEN_WIDTH / 2;
			int blobpos_y = SCREEN_HEIGHT / 2;
			int square_y = 0;
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

				//Get window surface
				screenSurface = SDL_GetWindowSurface(window);
				// draw background
				//SDL_BlitSurface(background, NULL, screenSurface, NULL);
				//SDL_UpdateWindowSurface(window);
				//Clear screen / fill with render draw color
				//SDL_RenderClear(renderer);
				//if (blobpos_y > SCREEN_HEIGHT || blobpos_y < 0 || blobpos_x > SCREEN_WIDTH || blobpos_x < 0)
				// set blob position
				sprite.x = blobpos_x;
				sprite.y = blobpos_y;

				SDL_RenderCopy(renderer, background, NULL, NULL);
				//Render texture to screen
				if (check_collision(sprite, enemy))
				{
					color = { 0, 255, 50 };
					blob_texture = frog_texture;
				}
				else 
				{
					color = { 255, 0, 50 };
					blob_texture = help_texture;
				}

				SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
				SDL_RenderFillRect(renderer, &enemy);
				SDL_RenderCopy(renderer, blob_texture, NULL, &sprite);


				//square_y++;
				//Renderer color
				
				// 255, 0, 0 
				//  r   g   b
				// 255, 255, 0 x
				// 0, 255, 0 x
				// 0, 255, 255 x
				// 0, 0, 255
				// 255, 0, 255
				// 255, 0, 0
				//if (color.g < 200 && color.r == 200)
				//	color.g++;
				//else if (color.r > 50 && color.g == 200)
				//	color.r--;
				//else if (color.b < 200 && color.g == 200)
				//	color.b++;
				//else if (color.g > 50 && color.b == 200)
				//	color.g--;
				//else if (color.r < 200 && color.b == 200)
				//	color.r++;
				//if (color.r == 50 && color.g == 50 && color.b > 50)
				//	color = { 200, 0, 0 };

				//printf("(%i, %i, %i)\n", color.r, color.g, color.b);

				//SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
				//SDL_Rect square1 = { 100, square_y, 100, 100 };
				////SDL_RenderFillRect(renderer, &square1);

				//SDL_SetRenderDrawColor(renderer, color.b, color.r, color.g, 255);
				//SDL_Rect square2 = { 300, square_y, 100, 100 };
				//SDL_RenderDrawRect(renderer, &square2);

				//if (square_y > SCREEN_HEIGHT)
				//	square_y = -100;

				//Update screen
				SDL_RenderPresent(renderer);
			}
		}
	}

	// free surfaces
	//SDL_FreeSurface(background);
	//background = NULL;
	//SDL_FreeSurface(blob);
	//blob = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	//int i;
	//scanf_s("%d", &i);
	return 0;
}

SDL_Texture* load_texture(std::string path)
{
	//Load image at specified path
	SDL_Texture* new_texture = NULL;
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
		if (new_texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loaded_surface);
	}

	return new_texture;
}

bool check_collision(SDL_Rect a, SDL_Rect b)
{
	//Sides of colliders
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Sides of a
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;
	
	// Sides of b
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	// Check collision
	if (bottomA <= topB)
		return false;
	if (topA >= bottomB)
		return false;

	if (leftA >= rightB)
		return false;
	if (rightA <= leftB)
		return false;

	//If none of the sides from A are outside B
	return true;
}
