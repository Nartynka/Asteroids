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
	void operator-=(Vec2 b) {
		x -= b.x;
		y -= b.y;
	}
	Vec2 operator*(float b) {
		Vec2 temp = { x, y };
		temp.x *= b;
		temp.y *= b;
		return temp;
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

//struct SizeComponent
//{
//	SizeVec2 size;
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
	TextureComponent textureComp = {};
	//PositionComponent positionComp;
};

struct Asteroid
{
	MovementComponent movementComp;
	TextureComponent textureComp = {};
};

void move(MovementComponent& moveComp, float dt)
{
	moveComp.position += moveComp.velocity * dt;

}

bool is_outside_screen(const MovementComponent& moveComp, const TextureComponent& sizeComp)
{
	if (moveComp.position.y < 0 || (moveComp.position.y + sizeComp.size.h > SCREEN_HEIGHT) || moveComp.position.x < 0 || (moveComp.position.x + sizeComp.size.w > SCREEN_WIDTH))
		return true;

	return false;
}

void render(const TextureComponent& textureComp, const MovementComponent& moveComp)
{
	SDL_Rect a = { (int)moveComp.position.x, (int)moveComp.position.y, textureComp.size.w, textureComp.size.h };
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

SDL_Texture* load_texture(std::string path, SizeVec2& size)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	assert(loaded_surface != nullptr && "Unable to load image\n");

	new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	assert(new_texture != nullptr && "Unable to create texture from image\n");

	size = { loaded_surface->w, loaded_surface->h };

	SDL_FreeSurface(loaded_surface);
	loaded_surface = NULL;

	return new_texture;
}

int main(int argc, char* args[])
{
	float dt = (float)SDL_GetTicks();
	float lastTime = 0.f;
	const float desiredDt = (1 / 60.f) * 1000; // 60 FPS

	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0 && "SDL could not initialize!");

	window = SDL_CreateWindow("Does this work", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	assert(window != nullptr && "Window could not be created!");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	assert(renderer != nullptr && "Renderer could not be created!");

	result = IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG;
	assert(result && "SDL_image could not initialize!");

	Player player;
	Asteroid asteroid;
	player.textureComp.texture = load_texture("ship.png", player.textureComp.size);
	assert(player.textureComp.texture != nullptr && "Player texture could not be created!");
	asteroid.textureComp.texture = load_texture("asteroids/asteroid-1.png", asteroid.textureComp.size);
	assert(asteroid.textureComp.texture != nullptr && "Asteroid texture could not be created!");

	player.movementComp.position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	asteroid.movementComp.position = { 100, 200 };
	asteroid.movementComp.velocity = { 0.1f, 0.1f };

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

			/* Player */
			handle_input(player.movementComp);
			move(player.movementComp, dt);
			if (is_outside_screen(player.movementComp, player.textureComp))
				player.movementComp.position -= player.movementComp.velocity * dt;

			/* Asteroid */
			move(asteroid.movementComp, dt);

			/* Render */
			SDL_RenderClear(renderer);

			render(player.textureComp, player.movementComp);

			if (asteroid.movementComp.position.x < SCREEN_WIDTH && asteroid.movementComp.position.y < SCREEN_HEIGHT)
				render(asteroid.textureComp, asteroid.movementComp);
			else
				asteroid.movementComp.position = { 0.f, (float)-asteroid.textureComp.size.h };

			SDL_RenderPresent(renderer);

			lastTime = (float)SDL_GetTicks();
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}