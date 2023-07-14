#include "Systems.h"
#include <Entity/Entity.h>

const int SPEED = 300;

void check_visibility(EntityAllocator* entity_alloc, Entity& entity, MovementComponent& mov_comp, float dt);

void move(float dt)
{
	EntityAllocator* entity_alloc = EntityAllocator::Get();
	ComponentAllocator* comp_alloc = ComponentAllocator::Get();

	for (unsigned int i = 0; i < entity_alloc->entities.size(); i++)
	{
		Entity& curr_entity = entity_alloc->entities.data()[i];
		int mov_comp_id = curr_entity.comp_ids[Components::MOVEMENT_COMPONENT];
		if (mov_comp_id == -1)
			continue;

		MovementComponent mov_comp = comp_alloc->movement_components[mov_comp_id];

		curr_entity.position += mov_comp.velocity * SPEED * dt;

		check_visibility(entity_alloc, curr_entity, mov_comp, dt);

		curr_entity.center = { curr_entity.position.x + (curr_entity.size.x / 2), curr_entity.position.y + (curr_entity.size.y / 2) };

		if (curr_entity.is_rotating)
			curr_entity.rotation += dt * 100;
	}
}

void check_visibility(EntityAllocator* entity_alloc, Entity& entity, MovementComponent& mov_comp, float dt)
{
	if (entity.HasComponent(PLAYER))
	{
		Vec2 top_pos = { entity.position.x + entity.size.x, entity.position.y + entity.size.y };
		if (entity.position.x < 0 || top_pos.x > SCREEN_WIDTH || entity.position.y < 0 || top_pos.y > SCREEN_HEIGHT)
		{
			entity.position -= mov_comp.velocity * SPEED * dt;
		}
	}
	else if (entity.position.x < -entity.size.x || entity.position.x > SCREEN_WIDTH || entity.position.y < -entity.size.y || entity.position.y > SCREEN_HEIGHT)
	{
		entity_alloc->QueueDestroy(entity.id);
	}
}