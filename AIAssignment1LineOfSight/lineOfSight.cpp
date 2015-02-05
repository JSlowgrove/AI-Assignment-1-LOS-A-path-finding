#include "lineOfSight.h"

/**************************************************************************************************************/

/*check if two positions can see each other*/
bool LOS::lineOfSight(Vec2 a, Vec2 b, Map* map)
{
	/*initialise the test area*/
	int minX, maxX, minY, maxY;
	minX = maxX = minY = maxY = 0;

	/*check for the smallest x*/
	if (a.x < b.x)
	{
		/*initialise the min tile using a and max tile using b*/
		minX = (int)(a.x / 32);
		maxX = (int)((b.x + 30) / 32);
	}
	else
	{
		/*initialise the min tile using b and max tile using a*/
		minX = (int)(b.x / 32);
		maxX = (int)((a.x + 30) / 32);
	}

	/*check for the smallest y*/
	if (a.y < b.y)
	{
		/*initialise the min tile using a and max tile using b*/
		minY = (int)(a.y / 32);
		maxY = (int)((b.y + 30) / 32);
	}
	else
	{
		/*initialise the min tile using b and max tile using a*/
		minY = (int)(b.y / 32);
		maxY = (int)((a.y + 30) / 32);
	}

	/*test only the tiles within the max and min y tiles*/
	for (int i = minY; i < maxY; i++)
	{
		/*test only the tiles within the max and min tiles on the x axis*/
		for (int j = minX; j < maxX; j++)
		{
			bool collision = false;
			/*
			A---------B
			|         |
			|         |
			|         |
			|         |
			|         |
			C---------D
			*/
			/*AB test*/
			if (lineLineIntersectionCheck(a, b, Vec2(j * 32, i * 32), Vec2((j + 1) * 32, i * 32), 'x'))
			{
				/*collision*/
				collision = true;
			}
			/*AC test*/
			if (lineLineIntersectionCheck(a, b, Vec2(j * 32, i * 32), Vec2(j * 32, (i + 1) * 32), 'y'))
			{
				/*collision*/
				collision = true;
			}
			/*CD test*/
			if (lineLineIntersectionCheck(a, b, Vec2(j * 32, (i + 1) * 32), Vec2((j + 1) * 32, (i + 1) * 32), 'x'))
			{
				/*collision*/
				collision = true;
			}
			/*BD test*/
			if (lineLineIntersectionCheck(a, b, Vec2((j + 1) * 32, (i + 1) * 32), Vec2((j + 1) * 32, (i + 1) * 32), 'y'))
			{
				/*collision*/
				collision = true;
			}

			/*if there has been a collision*/
			if (collision)
			{
				/*if the collision is a wall*/
				if (map->getMapPositionType(j, i) == 'w')
				{
					/*the creature is out of sight*/
					return false;
				}
			}
		}
	}
	/*the creature is still in sight*/
	return true;
}

/**************************************************************************************************************/

/*check if two lines intersect*/
bool LOS::lineLineIntersectionCheck(Vec2 a, Vec2 b, Vec2 c, Vec2 d, char axis)
{
	/*y=mx+c*/
	/*work out the gradient of the line ab*/
	float m = 0.0f;
	/*check it will not divide by 0*/
	if (b.x - a.x != 0.0f)
	{
		/*work out m using m = (y1-y0)/(x1-x0)*/
		m = (b.y - a.y) / (b.x - a.x);
	}

	/*work out c using c=y-mx*/
	float c0 = a.y - (m * a.x);

	/*initialise x & y*/
	float y = 0.0f;
	float x = 0.0f;

	/*test the axis*/
	switch (axis)
	{
	/*if the axis is the x axis*/
	case 'x':
		/*work out the x using x=(y-c)/m*/
		x = (c.y - c0) / m;
		/*if the x is on the line*/
		if (x >= c.x && x <= d.x)
		{
			/*the lines intersect*/
			return true;
		}
		break;
	/*if the axis is the y axis*/
	case 'y':
		/*work out the y using y=mx+c*/
		y = (m * c.x) + c0;
		/*if the y is on the line*/
		if (y >= c.y && y <= d.y)
		{
			/*the lines intersect*/
			return true;
		}
		break;
	}

	/*the lines do not intersect*/
	return false;
}

/**************************************************************************************************************/

/*draw the tiles on the line of sight*/
void LOS::drawLineOfSight(Vec2 a, Vec2 b, Map* map, SDL_Renderer* renderer)
{
	/*creates a rectangle*/
	SDL_Rect box;

	/*initialise the test area*/
	int minX, maxX, minY, maxY;
	minX = maxX = minY = maxY = 0;

	/*check for the smallest x*/
	if (a.x < b.x)
	{
		/*initialise the min tile using a and max tile using b*/
		minX = (int)(a.x / 32);
		maxX = (int)((b.x + 30) / 32);
	}
	else
	{
		/*initialise the min tile using b and max tile using a*/
		minX = (int)(b.x / 32);
		maxX = (int)((a.x + 30) / 32);
	}

	/*check for the smallest y*/
	if (a.y < b.y)
	{
		/*initialise the min tile using a and max tile using b*/
		minY = (int)(a.y / 32);
		maxY = (int)((b.y + 30) / 32);
	}
	else
	{
		/*initialise the min tile using b and max tile using a*/
		minY = (int)(b.y / 32);
		maxY = (int)((a.y + 30) / 32);
	}

	/*test only the tiles within the max and min y tiles*/
	for (int i = minY; i < maxY; i++)
	{
		/*test only the tiles within the max and min tiles on the x axis*/
		for (int j = minX; j < maxX; j++)
		{
			bool collision = false;
			/*
			A---------B
			|         |
			|         |
			|         |
			|         |
			|         |
			C---------D
			*/
			/*AB test*/
			if (lineLineIntersectionCheck(a, b, Vec2(j * 32, i * 32), Vec2((j + 1) * 32, i * 32), 'x'))
			{
				/*collision*/
				collision = true;
			}
			/*AC test*/
			if (lineLineIntersectionCheck(a, b, Vec2(j * 32, i * 32), Vec2(j * 32, (i + 1) * 32), 'y'))
			{
				/*collision*/
				collision = true;
			}
			/*CD test*/
			if (lineLineIntersectionCheck(a, b, Vec2(j * 32, (i + 1) * 32), Vec2((j + 1) * 32, (i + 1) * 32), 'x'))
			{
				/*collision*/
				collision = true;
			}
			/*BD test*/
			if (lineLineIntersectionCheck(a, b, Vec2((j + 1) * 32, (i + 1) * 32), Vec2((j + 1) * 32, (i + 1) * 32), 'y'))
			{
				/*collision*/
				collision = true;
			}

			/*if there has been a collision*/
			if (collision)
			{
				/*if the collision is a wall*/
				if (map->getMapPositionType(j, i) == 'w')
				{
					/*set the draw colour to magenta*/
					SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
				}
				/*if the collision is with an empty tile*/
				else
				{
					/*set the draw colour to orange*/
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xA5, 0x00, 0xFF);
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

	/*set the draw colour to white*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/*update the box for the test area*/
	box.x = minX * 32;
	box.y = minY * 32;
	box.w = (maxX * 32) - (minX * 32);
	box.h = (maxY * 32) - (minY * 32);

	/*draw the test area outline*/
	SDL_RenderDrawRect(renderer, &box);
}