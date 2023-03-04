#include <SDL.h>
#include <SDL_image.h>
#include <cassert> 
#include <vector>

#include "Components/Components.h"
#include "Systems/InputSystem.h"
#include "Systems/MoveSystem.h"
#include "Systems/RenderSystem.h"

int CURR_ID = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

/*
	Player Needs:
	- Position	PositionComponent (Vec2)
	- Texture	TextureComponent  (SDL_Texture*)
	- Velocity	MovementComponent (Vec2)
	- Rect/Size	BoxComponent?	  (SDL_Rect)
	- Rotation	RotationComponent (Double)
*/

struct Player
{
	MovementComponent movementComp;
	TextureComponent textureComp = {};
	//PositionComponent positionComp;
};

struct Asteroid
{
	MovementComponent movementComp;
	TextureComponent textureComp = {};
};



SDL_Texture* load_texture(const char* path, Vec2& size)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* loaded_surface = IMG_Load(path);
	assert(loaded_surface != nullptr && "Unable to load image\n");

	new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	assert(new_texture != nullptr && "Unable to create texture from image\n");

	size = { static_cast<float>(loaded_surface->w), (float)loaded_surface->h };

	SDL_FreeSurface(loaded_surface);
	loaded_surface = NULL;

	return new_texture;
}

int main(int argc, char* args[])
{
	float dt = (float)(SDL_GetTicks() / 1000.f);
	float lastTime = 0.f;
	const float DESIRED_DT = 1 / 60.f; // 60 FPS

	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0 && "SDL could not initialize!");

	window = SDL_CreateWindow("Does this work", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	assert(window != nullptr && "Window could not be created!");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	assert(renderer != nullptr && "Renderer could not be created!");

	result = IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG;
	assert(result && "SDL_image could not initialize!");

	/*Uint64_t id = CreateEntity("Player");
	AddMovementComponent(id);
	AddRenderComponent(id, "ship.png");

	ResolveInput(inputcomponent, movementcomponent)
	*/
	Player player;
	Asteroid asteroid;
	player.textureComp.texture = load_texture("res/ship.png", player.textureComp.size);
	assert(player.textureComp.texture != nullptr && "Player texture could not be created!");
	asteroid.textureComp.texture = load_texture("res/asteroids/asteroid-1.png", asteroid.textureComp.size);
	assert(asteroid.textureComp.texture != nullptr && "Asteroid texture could not be created!");

	player.movementComp.position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	asteroid.movementComp.position = { 100, 200 };
	asteroid.movementComp.velocity = { 0.1f, 0.1f };

	bool quit = false;
	SDL_Event event;
	//Game loop
	while (!quit)
	{
		dt = (SDL_GetTicks() - lastTime) / 1000;

		if (dt >= DESIRED_DT)
		{
			/*
			input();
			update();
			draw();
			*/

			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
					quit = true;
			}

			/* Player */
			handle_input(player.movementComp);
			move(player.movementComp, dt);
			if (is_outside_screen(player.movementComp, player.textureComp))
				player.movementComp.position -= player.movementComp.velocity * dt;

			///* Asteroid */
			move(asteroid.movementComp, dt);

			///* Render */
			SDL_RenderClear(renderer);

			render(renderer, player.textureComp, player.movementComp);

			if (asteroid.movementComp.position.x < SCREEN_WIDTH && asteroid.movementComp.position.y < SCREEN_HEIGHT)
				render(renderer, asteroid.textureComp, asteroid.movementComp);
			else
				asteroid.movementComp.position = { 0.f, (float)-asteroid.textureComp.size.y };

			SDL_RenderPresent(renderer);

			lastTime = (float)SDL_GetTicks();
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}