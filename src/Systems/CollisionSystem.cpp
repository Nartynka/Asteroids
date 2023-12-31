#include "Systems.h"
#include <Entity/Entity.h>

int points = 0;
bool game_over = false;

void check_collision()
{
	EntityAllocator* entity_alloc = EntityAllocator::Get();
	size_t count = entity_alloc->entities.size();

	for (int i = 0; i < count; i++)
	{
		Entity& entity_a = entity_alloc->entities.data()[i];

		float x1 = entity_a.center.x;
		float y1 = entity_a.center.y;
		float r1 = entity_a.radius;

		for (int j = i + 1; j < count; j++)
		{
			Entity& entity_b = entity_alloc->entities.data()[j];

			float x2 = entity_b.center.x;
			float y2 = entity_b.center.y;
			float r2 = entity_b.radius;

			// check if two circles intersects with each other
			double result = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
			if (result < ((r1 + r2) * (r1 + r2)))
			{
				if ((entity_a.HasComponent(Components::PLAYER) && entity_b.HasComponent(Components::ASTEROID)) || (entity_b.HasComponent(Components::PLAYER) && entity_a.HasComponent(Components::ASTEROID)))
				{
					game_over = true;
					entity_alloc->QueueDestroy(entity_a.id);
					entity_alloc->QueueDestroy(entity_b.id);
				}
				else if ((entity_a.HasComponent(Components::ASTEROID) && entity_b.HasComponent(Components::BULLET)) || (entity_b.HasComponent(Components::ASTEROID) && entity_a.HasComponent(Components::BULLET)))
				{
					points++;
					entity_alloc->QueueDestroy(entity_a.id);
					entity_alloc->QueueDestroy(entity_b.id);
				}
			}
		}
	}
}