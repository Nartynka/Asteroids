#include "Spawners.h"
#include "Components/Components.h"
#include "Entity/Entity.h"

static ComponentAllocator* comp_alloc = ComponentAllocator::Get();
static EntityAllocator* entity_alloc = EntityAllocator::Get();

int CreateAsteroid(Vec2 position, Vec2 velocity, float rotation, bool is_rotating, SDL_Renderer* renderer)
{
	int idx = entity_alloc->CreateEntity(position, "res/asteroids/asteroid-1.png", renderer, 60.f, rotation, is_rotating);
	comp_alloc->CreateMovementComponent(idx, velocity);

	return idx;
}

int CreatePlayer(Vec2 position, SDL_Renderer* renderer)
{
	int idx = entity_alloc->CreateEntity(position, "res/ship.png", renderer, 45.f);
	comp_alloc->CreateMovementComponent(idx, {});
	return idx;
}

constexpr float M_PI = 3.14159265358979323846;

int CreateProjectile(Vec2 shooter_pos, Vec2 shooter_size, float shooter_rotation, SDL_Renderer* renderer)
{
	int idx = entity_alloc->entities.size();

	// deg to rad
	float rotation = shooter_rotation * M_PI / 180;

	// calculate shooter forward vector
	Vec2 forward_vec = { sin(rotation), -cos(rotation) };
	// add some speed so that bullets will be faster than the shooter
	Vec2 forward_vel = { forward_vec.x * 1, forward_vec.y * 1 };

	// Calculate the offset from the center of the shooter to the firing point
	float distance = shooter_size.y-4.f;
	float offset_x = distance * sin(rotation);
	float offset_y = distance * -cos(rotation);

	// Calculate the firing point
	Vec2 firing_point = {
		shooter_pos.x + shooter_size.x / 2 + offset_x,
		shooter_pos.y + shooter_size.y / 2 + offset_y
	};

	entity_alloc->CreateEntity(firing_point, "res/bullet.png", renderer, 10.f, shooter_rotation);
	comp_alloc->CreateMovementComponent(idx, forward_vel);

	return idx;
}