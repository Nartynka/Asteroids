#include "Systems.h"
#include <Components/Components.h>
#include <Entity/Entity.h>

//@TODO: These don't belong here
const int SPEED = 300;

//@TODO: For now we can once again leave the screen
void move(float dt)
{
	EntityAllocator* entity_alloc = EntityAllocator::Get();
	ComponentAllocator* comp_alloc = ComponentAllocator::Get();

	for (unsigned int i = 0; i < entity_alloc->entities.size(); i++)
	{
		int mov_comp_id = entity_alloc->entities[i].comp_ids[Components::MOVEMENT_COMPONENT];
		if (mov_comp_id == -1)
			continue;

		MovementComponent mov_comp = comp_alloc->movement_components[mov_comp_id];
		entity_alloc->entities[i].position.x += mov_comp.velocity.x * SPEED * dt;
		entity_alloc->entities[i].position.y += mov_comp.velocity.y * SPEED * dt;

		entity_alloc->entities[i].center += {mov_comp.velocity.x * SPEED * dt, mov_comp.velocity.y * SPEED * dt };

		if (entity_alloc->entities[i].is_rotating)
			entity_alloc->entities[i].rotation += dt * 100;
	}

}
