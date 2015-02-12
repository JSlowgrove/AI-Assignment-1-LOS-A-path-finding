#include "creature.h"

/**************************************************************************************************************/

/*Constructs the creature object*/
Creature::Creature(Texture * inTexture, Vec2 inPos, Vec2 inSource, int inSpriteW, int inSpriteH, int w, int h)
	: Entity(inTexture, inPos, inSource, inSpriteW, inSpriteH, w, h)
{
	/*initialises the velocities*/
	velocities = { 0.0f, 0.0f };
	/*initialise the min and max tiles*/
	minX = maxX = (int)((inPos.x - 1) / 32);
	minY = maxY = (int)((inPos.y - 1) / 32);
}

/**************************************************************************************************************/

/*Destructs the creature object*/
Creature::~Creature()
{
}

/**************************************************************************************************************/

/*Updates the creature position*/
void Creature::updatePosition(float dt)
{
	/*updates the position using the velocities and dt*/
	position += (velocities * dt);

	/*update the tiles*/
	minX = (int)(position.x / 32);
	maxX = (int)((position.x + width) / 32);
	minY = (int)(position.y / 32);
	maxY = (int)((position.y + height) / 32);
}

/**************************************************************************************************************/

/*sets the velocities*/
void Creature::setVelocities(Vec2 inVelocities)
{
	/*sets the velocities*/
	velocities = inVelocities;
}

/**************************************************************************************************************/

/*gets the velocities*/
Vec2 Creature::getVelocities()
{
	/*returns the velocities*/
	return velocities;
}

/**************************************************************************************************************/

/*displays the tiles the creature occupies*/
void Creature::displayTiles(SDL_Renderer* renderer, Map* map)
{
	/*creates a rectangle using the tiles*/
	SDL_Rect box;
	box.x = minX * 32;
	box.y = minY * 32;
	box.w = 32 + ((maxX - minX) * 32);
	box.h = 32 + ((maxY - minY) * 32);

	/*set the draw colour to green*/
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);

	/*draw the tiles outline*/
	SDL_RenderDrawRect(renderer, &box);

	/*check for collisions up*/
	if (velocities.y < 0)
	{
		/*display the tested tiles*/
		displayCollisionTest(renderer, map, 0, minY, minX, maxX);
	}
	/*check for collisions down*/
	if (velocities.y > 0)
	{
		/*display the tested tiles*/
		displayCollisionTest(renderer, map, maxY, map->getNumberOfYObjects() - 1, minX, maxX);
	}
	/*check for collisions left*/
	if (velocities.x < 0)
	{
		/*display the tested tiles*/
		displayCollisionTest(renderer, map, minY, maxY, 0, minX);
	}
	/*check for collisions right*/
	if (velocities.x > 0)
	{
		/*display the tested tiles*/
		displayCollisionTest(renderer, map, minY, maxY, maxX, map->getNumberOfXObjects() - 1);
	}
}

/**************************************************************************************************************/

/*displays the tiles being tested for collision*/
void Creature::displayCollisionTest(SDL_Renderer* renderer, Map* map, int minI, int maxI, int minJ, int maxJ)
{
	/*creates a rectangle*/
	SDL_Rect box;

	/*test only the tiles within the max and min tiles on the opposite axis*/
	for (int i = minI; i <= maxI; i++)
	{
		/*test only the tiles within the min and max tiles on the current axis*/
		for (int j = minJ; j <= maxJ; j++)
		{
			/*check if the type of the tile*/
			switch (map->getMapPositionType(j, i))
			{
				/*if tile is a wall*/
			case 'w':
				/*set the draw colour to red*/
				SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
				break;

			/*if tile is anything else*/
			default:
				/*set the draw colour to cyan*/
				SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
				break;
			}
			/*update the box for the tile*/
			box.x = j * 32;
			box.y = i * 32;
			box.w = box.h = 32;

			/*draw the tiles outline*/
			SDL_RenderDrawRect(renderer, &box);
		}
	}
}

/**************************************************************************************************************/

/*tests if the Creature collides with a Wall and performs an act upon the result*/
void Creature::collisionUpdate(Map* map, float dt)
{
	/*check for collisions up*/
	if (velocities.y < 0)
	{
		velocities.y = collision(map, dt, velocities.y, position.y, 0, minY, minX, maxX, 'u');
	}
	/*check for collisions down*/
	if (velocities.y > 0)
	{
		velocities.y = collision(map, dt, velocities.y, position.y, maxY, map->getNumberOfYObjects()-1, minX, maxX, 'd');
	}
	/*check for collisions left*/
	if (velocities.x < 0)
	{
		velocities.x = collision(map, dt, velocities.x, position.x, minY, maxY, 0, minX, 'l');
	}
	/*check for collisions right*/
	if (velocities.x > 0)
	{
		velocities.x = collision(map, dt, velocities.x, position.x, minY, maxY, maxX, map->getNumberOfXObjects()-1, 'r');
	}
}

/**************************************************************************************************************/

/*tests if the Creature collides with a Wall in a certain direction and performs an act upon the result*/
float Creature::collision(Map* map, float dt, float velocity, float currentPos, int minI, int maxI, int minJ, int maxJ, char axis)
{
	/*test only the tiles within the max and min tiles on the opposite axis*/
	for (int i = minI; i <= maxI; i++)
	{
		/*test only the tiles within the min and max tiles on the current axis*/
		for (int j = minJ; j <= maxJ; j++)
		{
			/*check if the type of the tile*/
			switch (map->getMapPositionType(j, i))
			{
			/*if tile is a wall*/
			case 'w':
				/*perform a check depending on the axis to test*/
				switch (axis)
				{
				/*check if its is interesting and going up*/
				case 'u':
					if (map->getWall(map->getMapPositionIndex(j, i))->getPosition().y
						+ map->getWall(map->getMapPositionIndex(j, i))->getHeight()
						>= currentPos + (velocity * dt))
					{
						/*stop the player in the given axis*/
						velocity = 0.0f;
					}
					break;

				/*check if its is interesting and going down*/
				case 'd':
					if (map->getWall(map->getMapPositionIndex(j, i))->getPosition().y
						<= currentPos + (velocity * dt) + height)
					{
						/*stop the player in the given axis*/
						velocity = 0.0f;
					}
					break;

				/*check if its is interesting and going left*/
				case 'l':
					if (map->getWall(map->getMapPositionIndex(j, i))->getPosition().x
						+ map->getWall(map->getMapPositionIndex(j, i))->getWidth()
						>= currentPos + (velocity * dt))
					{
						/*stop the player in the given axis*/
						velocity = 0.0f;
					}
					break;
				
				/*check if its is interesting and going right*/
				case 'r':
					if (map->getWall(map->getMapPositionIndex(j, i))->getPosition().x
						<= currentPos + (velocity * dt) + width)
					{
						/*stop the player in the given axis*/
						velocity = 0.0f;
					}
					break;
				}				
				break;
			}
		}
	}

	/*return the resultant velocity*/
	return velocity;
}

/**************************************************************************************************************/

/*tests if the Creature collides with an Entity and performs an act upon the result*/
void Creature::collisionUpdate(Entity* entity, float dt)
{
	/*check for collisions*/
	if (entity->getPosition().y + entity->getHeight() >= position.y + (velocities.y * dt)
		&& entity->getPosition().y <= position.y + (velocities.y * dt) + height
		&& entity->getPosition().x + entity->getWidth() >= position.x + (velocities.x * dt)
		&& entity->getPosition().x <= position.x + (velocities.x * dt) + width)
	{
		velocities = { 0.0f, 0.0f };
	}
}