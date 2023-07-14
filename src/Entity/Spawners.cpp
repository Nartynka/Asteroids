#include "Spawners.h"
#include "Components/Components.h"
#include "Entity/Entity.h"

static ComponentAllocator* comp_alloc = ComponentAllocator::Get();
static EntityAllocator* entity_alloc = EntityAllocator::Get();

int CreateAsteroid(Vec2 position, Vec2 velocity, float rotation, bool is_rotating, SDL_Renderer* renderer)
{
	int entity_id = entity_alloc->CreateEntity(position, "res/asteroids/asteroid-1.png", renderer, 60.f, rotation, is_rotating);
	comp_alloc->CreateMovementComponent(entity_id, velocity);
	comp_alloc->CreateAsteroidComponent(entity_id);

	return entity_id;
}

int CreatePlayer(Vec2 position, SDL_Renderer* renderer)
{
	int entity_id = entity_alloc->CreateEntity(position, "res/ship.png", renderer, 45.f);
	comp_alloc->CreateMovementComponent(entity_id, {});
	comp_alloc->CreatePlayerComponent(entity_id);
	return entity_id;
}

constexpr float M_PI = 3.14159265358979323846f;

int CreateProjectile(Vec2 shooter_pos, Vec2 shooter_size, float shooter_rotation, SDL_Renderer* renderer)
{
	// deg to rad
	float rotation = shooter_rotation * M_PI / 180;

	// calculate shooter forward vector
	Vec2 forward_vec = { (float)sin(rotation), (float)-cos(rotation) };
	// add some speed so that bullets will be faster than the shooter
	Vec2 forward_vel = { forward_vec.x * 1, forward_vec.y * 1 };

	// Calculate the offset from the center of the shooter to the firing point
	float distance = shooter_size.y - 4.f;
	float offset_x = distance * (float)sin(rotation);
	float offset_y = distance * (float)-cos(rotation);

	// Calculate the firing point
	Vec2 firing_point = {
		shooter_pos.x + shooter_size.x / 2 + offset_x,
		shooter_pos.y + shooter_size.y / 2 + offset_y
	};

	int entity_id = entity_alloc->CreateEntity(firing_point, "res/bullet.png", renderer, 10.f, shooter_rotation);
	comp_alloc->CreateMovementComponent(entity_id, forward_vel);
	comp_alloc->CreateBulletComponent(entity_id);

	return entity_id;
}

void RandomAsteroid(SDL_Renderer* renderer)
{
	// <-0.999.., 0.999..>
	Vec2 vel = { (float)rand() / (float)RAND_MAX , (float)rand() / (float)RAND_MAX };
	Vec2 pos;

	bool spawn_on_x = rand() % 2;
	if (spawn_on_x)
	{
		int pos_x = rand() % 1000;
		int pos_y = (rand() % 2) ? 700 : 0;
		// pos.y == 0 then vel must be positive
		// pos.y == 700 then vel must be negative

		// which is better?
		//vel.y = pos_y ? -abs(vel.y) : abs(vel.y);

		if (pos_y)
			vel.y = -abs(vel.y);
		else
			vel.y = abs(vel.y);

		pos = { (float)pos_x, (float)pos_y };
	}
	else
	{
		int pos_x = (rand() % 2) ? 1000 : 0;
		int pos_y = rand() % 700;
		// pos.x == 0 then vel must be positive
		// pos.x == 1000 then vel must be negative

		// which is better?
		// vel.x = pos_x ? -abs(vel.x) : abs(vel.x);

		if (pos_x)
			vel.x = -abs(vel.x);
		else
			vel.x = abs(vel.x);

		pos = { (float)pos_x, (float)pos_y };
	}

	if (pos.y > 500 && vel.y > 0)
		vel.y = -vel.y;
	if (pos.x > 800 && vel.x > 0)
		vel.x = -vel.x;

	int rotation = (rand() % 180) + 1;

	CreateAsteroid(pos, vel, (float)rotation, true, renderer);
}
