#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h> // printf
#include <string>
#include <cassert> 

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

struct Vec2
{
	float x;
	float y;
	void operator+=(Vec2 b) {
		x += b.x;
		y += b.y;
	}
	Vec2 operator*(float b) {
		x *= b;
		y *= b;
		return { x, y };
	}
};

struct SizeVec2
{
	int w;
	int h;
};

//struct PositionComponent
//{
//	Vec2 position;
//};

struct TextureComponent
{
	SDL_Texture* texture;
	SizeVec2 size;
};

struct MovementComponent
{
	Vec2 velocity = { 0,0 };
	Vec2 position = { 0,0 };
};

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
	TextureComponent textureComp;
	//PositionComponent positionComp;
};

void move(MovementComponent& moveComp, float dt)
{
	moveComp.position += moveComp.velocity * dt;
}

void render(const TextureComponent& textureComp, const MovementComponent& moveComp)
{
	SDL_Rect a = { moveComp.position.x, moveComp.position.y, textureComp.size.w, textureComp.size.h };
	SDL_RenderCopy(renderer, textureComp.texture, NULL, &a);
}

void handle_input(MovementComponent& moveComp)
{
	moveComp.velocity = { 0,0 };
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W])
	{
		moveComp.velocity.y = -1.0;
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S])
	{
		moveComp.velocity.y = 1.0;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A])
	{
		moveComp.velocity.x = -1.0;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D])
	{
		moveComp.velocity.x = 1.0;
	}
}

SDL_Texture* load_texture(std::string path, SizeVec2 &size)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	assert(loaded_surface != nullptr && "Unable to load image\n");

	new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	assert(new_texture != nullptr && "Unable to create texture from image\n");

	size = {loaded_surface->w, loaded_surface->h };

	SDL_FreeSurface(loaded_surface);
	loaded_surface = NULL;
	
	return new_texture;
}

int main(int argc, char* args[])
{
	float dt = SDL_GetTicks();
	float lastTime = 0.f;
	const float desiredDt = (1 / 60.f)*1000; // 60 FPS

	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0 && "SDL could not initialize!\n");

	window = SDL_CreateWindow("Does this work", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	assert(window != nullptr && "Window could not be created!\n");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	assert(renderer != nullptr && "Renderer could not be created!\n");

	result = IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG;
	assert(result && "SDL_image could not initialize! SDL_image Error: %s\n");

	Player player;
	player.textureComp.texture = load_texture("ship.png", player.textureComp.size);
	assert(player.textureComp.texture != nullptr && "Player texture could not be created!\n");

	player.movementComp.position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, };

	bool quit = false;
	SDL_Event event;
	//Game loop
	while (!quit)
	{
		dt = SDL_GetTicks() - lastTime;

		if (dt >= desiredDt)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
					quit = true;
			}

			handle_input(player.movementComp);
			move(player.movementComp, dt);

			SDL_RenderClear(renderer);
			render(player.textureComp, player.movementComp);
			lastTime = SDL_GetTicks();
			SDL_RenderPresent(renderer);
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}