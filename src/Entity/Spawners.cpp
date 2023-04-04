#include "Spawners.h"
#include "Components/Components.h"
#include "Entity/Entity.h"

static ComponentAllocator* comp_alloc = ComponentAllocator::Get();
static EntityAllocator* entity_alloc = EntityAllocator::Get();

int CreateAsteroid(Vec2 position, Vec2 velocity, float rotation, bool is_rotating)
{
	int idx = entity_alloc->CreateEntity(position, "res/asteroids/asteroid-1.png", rotation, is_rotating);
	comp_alloc->CreateMovementComponent(idx, velocity);
	return idx;
}

int CreatePlayer(Vec2 position)
{
	int idx = entity_alloc->CreateEntity(position, "res/ship.png");
	comp_alloc->CreateMovementComponent(idx, {});
	return idx;
}

constexpr float M_PI = 3.14159265358979323846;

int CreateProjectile(Vec2 shooter_pos, float shooter_rotation)
{
	int idx = entity_alloc->entities.size();

	// deg to rad
	float rotation = shooter_rotation * M_PI / 180;

	// calculate shooter forward vector
	Vec2 forward_vec = { sin(rotation), -cos(rotation) };
	// add some speed so that bullets will be faster than the shooter
	Vec2 forward_vel = { forward_vec.x * 2, forward_vec.y * 2 };

	// shooter_pos = { shooter_pos.x + (15 * forward_vec.x), shooter_pos.y - (15 * forward_vec.y) };
	entity_alloc->CreateEntity(shooter_pos, "res/bullet.png", shooter_rotation);
	comp_alloc->CreateMovementComponent(idx, forward_vel);

	return idx;
}