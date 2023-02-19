#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>

//Screen size
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

// 60fps = ~10 pixel/s
//const int VELOCITY = 640;

SDL_Texture* load_texture(std::string path);
bool check_collision(SDL_Rect a, SDL_Rect b);

SDL_Texture* load_font(std::string path, std::string text);
//The window we'll be rendering to
SDL_Window* window = NULL;
//The surface contained by the window
SDL_Surface* screenSurface = NULL;
// Renderer for rendering images
SDL_Renderer* renderer = NULL;

SDL_Rect text_rect;

//Uint32 ticks = 0;
//float force = 10.0;
//bool apply_force = false;
//struct Vector2
//{
//	float x;
//	float y;
//};

int main(int argc, char* args[])
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		// Create window
		window = SDL_CreateWindow("Does this work", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (!window)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			// Create renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
				printf("Unable to create renderer! SDL Error: %s\n", SDL_GetError());

			// Initialize PNG loading
			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());

			// Initialize ttf loading
			if (TTF_Init() == -1)
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());

			SDL_Texture* text_texture = load_font("Fonts/PressStart.ttf", "Collision!!");

			// Start position of player at the center of the window
			SDL_Rect player = { SCREEN_WIDTH / 2 + 30, SCREEN_HEIGHT / 2 + 30, 60, 60 };
			double rotation = 0;
			int projectile_to_spawn = 0;

			std::vector<SDL_Rect*> projectiles;
			std::vector<SDL_Rect*> asteroids;

			SDL_Rect asteroid = { 50, 50, 120, 110};
			SDL_Rect asteroid2 = { SCREEN_WIDTH - 240, 50, 48, 47 };

			SDL_Rect asteroid3 = asteroid2;
			SDL_Rect asteroid4 = asteroid2;
			asteroid3.x = 0;
			asteroid3.y = 500;
			asteroid4.x = asteroid.x;
			asteroid4.y = 300;

			asteroids.push_back(&asteroid);
			asteroids.push_back(&asteroid2);
			asteroids.push_back(&asteroid3);
			asteroids.push_back(&asteroid4);

			SDL_Texture* ship_texture = load_texture("ship.png");
			SDL_Texture* asteroid_texture = load_texture("Asteroids/asteroid-1.png");
			SDL_Texture* asteroid_texture2 = load_texture("Asteroids/asteroid-2.png");
			SDL_Texture* asteroid_texture3 = load_texture("Asteroids/asteroid-3.png");

			if (ship_texture == NULL || asteroid_texture == NULL || asteroid_texture2 == NULL || asteroid_texture3 == NULL)
				printf("Unable to load images! SDL Error: %s\n", SDL_GetError());

			bool quit = false;
			SDL_Event event;

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
					if (event.type == SDL_KEYDOWN && event.key.repeat == 0 && (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_e))
						projectile_to_spawn++;
				}

				float vel_x = 0;
				float vel_y = 0;

				// if key is pressed then modify player position accordingly
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W])
				{
					rotation = 0;
					vel_y = -1.0;
					//apply_force = true;
				}
				//else apply_force = false;
				if (currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S])
				{
					rotation = 180;
					vel_y = 1.0;
					//apply_force = true;
				}
				//else apply_force = false;
				if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A])
				{
					rotation = -90;
					vel_x = -1.0;
					//force = 0.1;
					//apply_force = true;
				}
				//else apply_force = false;
				if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D])
				{
					rotation = 90;
					vel_x = 1.0;
					//force = -0.1;
					//apply_force = true;
				}

				// set background color to black
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				// fill screen with this color
				SDL_RenderClear(renderer);

				// If player is colliding render text
				if (check_collision(player, asteroid))
					SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

				/*
				//vel_x += factorX;
				//vel_y += factorY;
				//Uint32 time = SDL_GetTicks() - ticks;

				//float dt = time / 1000.f;
				//printf("tick: %u delta: %f\n", time, dt);
				//// set new player position
				//player.x += vel_x * dt;
				//player.y += vel_y * dt;


				//ticks = SDL_GetTicks();
				*/

				player.x += vel_x;
				player.y += vel_y;

				//Move player back if he went to far
				if ((player.y < 0) || (player.y + player.h > SCREEN_HEIGHT))
					player.y -= vel_y;
				if ((player.x < 0) || (player.x + player.w > SCREEN_WIDTH))
					player.x -= vel_x;

				/*int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				//printf("%u %u\n", mouseX, mouseY);

				//double angle = atan2(asteroid.y-(player.y+player.h/2), asteroid.x-(player.x+player.w/2));
				double angle = atan2(mouseY-(player.y + player.h / 2), mouseX-(player.x+player.w/2));
				double factorX = cos(angle);
				double factorY = sin(angle);

				double deg = (angle / M_PI * 180);
					
				printf("deg: %f factor: %f, %f\n", deg, factorX, factorY);
				player.x += factorX * 10;
				player.y += factorY * 10;

				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderDrawLine(renderer, mouseX, mouseY, (player.x + player.w / 2), (player.y + player.h / 2));*/

				/*float pos_x = player.x, pos_y = player.y;

				float timeStep = (SDL_GetTicks() - ticks) / 1000.f;
				ticks = SDL_GetTicks();
				//Move the dot left or right
				pos_x += vel_x * timeStep;
				pos_y += vel_y * timeStep;

				if (pos_x < 0)
					pos_x = 0;
				else if (pos_x > SCREEN_WIDTH - player.w)
					pos_x = SCREEN_WIDTH - player.w;
				if (pos_y < 0)
					pos_y = 0;
				else if (pos_y > SCREEN_HEIGHT - player.h)
					pos_y = SCREEN_HEIGHT - player.h;

				player.x = (int)pos_x;
				player.y = (int)pos_y;*/

				// Render player
				SDL_RenderCopyEx(renderer, ship_texture, NULL, &player, rotation, NULL, SDL_FLIP_NONE);

				int i = 1;
				for (SDL_Rect* a : asteroids)
				{
					if (i % 2 == 0)
					{
						a->x -= 1;
						a->y += 1;
					}
					else
					{
						a->x += 1;
						a->y += 1;
					}
					i++;
				}

				// Render Asteroid if it's on the screen
				if (asteroid.x < SCREEN_WIDTH && asteroid.y < SCREEN_HEIGHT)
					SDL_RenderCopy(renderer, asteroid_texture, NULL, &asteroid);
				else
				{
					asteroid.x = 0;
					asteroid.y = -asteroid.h;
				}
				if (asteroid2.x < SCREEN_WIDTH && asteroid2.y < SCREEN_HEIGHT)
					SDL_RenderCopy(renderer, asteroid_texture2, NULL, &asteroid2);
				else
				{
					asteroid2.x = SCREEN_WIDTH;
					asteroid2.y = -asteroid2.h;
				}
				if (asteroid3.x < SCREEN_WIDTH && asteroid3.y < SCREEN_HEIGHT)
					SDL_RenderCopy(renderer, asteroid_texture3, NULL, &asteroid3);
				else
				{
					asteroid3.x = -100;
					asteroid3.y = -asteroid3.h;
				}
				if (asteroid4.x < SCREEN_WIDTH && asteroid4.y < SCREEN_HEIGHT)
					SDL_RenderCopy(renderer, asteroid_texture2, NULL, &asteroid4);
				else
				{
					asteroid4.x = SCREEN_WIDTH;
					asteroid4.y = -asteroid4.h;
				}


				// Projectile

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				if (projectile_to_spawn > 0)
				{
					for (int i = 0; i < projectile_to_spawn; i++)
					{
						SDL_Rect point = { player.x + player.w / 2 - 5, player.y + player.h / 2 - 5, 10, 10 };
						projectiles.push_back(&point);
					}
					projectile_to_spawn = 0;
				}

				if (projectiles.size() > 0)
				{
					//int i = 1;
					double angle = rotation / 180 * M_PI;
					double factorY = -cos(angle);
					double factorX = sin(angle);
					for (SDL_Rect* p : projectiles)
					{
						//double angle = atan2(p->y - SCREEN_HEIGHT, p->x - SCREEN_WIDTH);

						p->x += factorX;
						p->y += factorY;

						if (p->x < SCREEN_WIDTH && p->x > 0 && p->y < SCREEN_HEIGHT && p->y > 0)
							SDL_RenderDrawRect(renderer, p);
						/*
						//else
						//	p = NULL;
						//int deltaX = asteroid.x - p.x;
						//int deltaY = asteroid.y - p.y;
						//int factorY = deltaY / deltaX;
						//p.x += 1;
						//p.y += factorY / 10;
						//if (deltaX > 0)
						//{
						//}
						//else
						//	printf("zero\n");
						//int delta_x = asteroid.x - p.x;
						//int delta_y = asteroid.y - p.y;

						//double angle = atan2(delta_y, delta_x);
						//double deg = angle / M_PI * 180;
						//printf("%u angle: %f \n", i, deg);
						//i++;
						*/
					}
				}

				// Update screen
				SDL_RenderPresent(renderer);
			}
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);
	//Quit SDL subsystems
	TTF_Quit();
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
		loaded_surface = NULL;
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

	// Sides of a collider
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	// Sides of b collider
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	// Check if they are not colliding
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

SDL_Texture* load_font(std::string path, std::string text)
{
	// load font
	TTF_Font* font = TTF_OpenFont(path.c_str(), 30);
	if (font == NULL)
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());

	SDL_Texture* text_texture = NULL;
	// Render text surface
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), { 255,255,255 });
	if (text_surface == NULL)
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	else
	{
		//Create texture from surface pixels
		text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		if (text_texture == NULL)
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());

		text_rect = { (SCREEN_WIDTH / 2) - (text_surface->w / 2), 10, text_surface->w, text_surface->h };

		SDL_FreeSurface(text_surface);
	}
	return text_texture;
}
