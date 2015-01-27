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
void Creature::displayTiles(SDL_Renderer* renderer)
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
}

/**************************************************************************************************************/

/*tests if the Creature collides with a Wall and performs an act upon the result*/
void Creature::collisionUpdate(Map* map, float dt)
{
	/*check for collisions up*/
	if (velocities.y < 0)
	{
		velocities.y = collision(map, dt, velocities.y, position.y, 0, minY, minX, maxX, 'y');
	}
	/*check for collisions down*/
	/*if (velocities.y > 0)
	{
		collision(map, dt);
	}*/
	/*check for collisions left*/
	if (velocities.x < 0)
	{
		velocities.x = collision(map, dt, velocities.x, position.x, minY, maxY, 0, minX, 'x');
	}
	/*check for collisions right*/
	/*if (velocities.x > 0)
	{
		collision(map, dt);
	}*/
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
				/*check if its is interesting*/
				case 'x':
					if (map->getWall(map->getMapPositionIndex(j, i))->getPosition().x
						+ map->getWall(map->getMapPositionIndex(j, i))->getWidth()
						>= currentPos + (velocity * dt))
					{
						/*stop the player in the given axis*/
						velocity = 0.0f;
					}
					break;

				/*check if its is interesting*/
				case 'y':
					if (map->getWall(map->getMapPositionIndex(j, i))->getPosition().y
						+ map->getWall(map->getMapPositionIndex(j, i))->getHeight()
						>= currentPos + (velocity * dt))
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