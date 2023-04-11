#include "Systems.h"
#include "Components/Components.h"
#include <stdio.h>
#include <Entity/Entity.h>

// How to reacts to collision?
bool check_collision()
{
	EntityAllocator* entity_alloc = EntityAllocator::Get();
	size_t count = entity_alloc->entities.size();

	for (int i = 0; i < count; i++)
	{
		float x1 = entity_alloc->entities[i].center.x;
		float y1 = entity_alloc->entities[i].center.y;
		float r1 = entity_alloc->entities[i].radius;

		for (int j = 1; j < count; j++)
		{
			if (i == j)
				continue;
			float x2 = entity_alloc->entities[j].center.x;
			float y2 = entity_alloc->entities[j].center.y;
			float r2 = entity_alloc->entities[j].radius;

			// check if two circles intersects with each other
			double result = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
			if (result < ((r1 + r2) * (r1 + r2)))
			{
				printf("Collision!!!!\n");
			}
		}
	}
	return true;
	//return false;
}