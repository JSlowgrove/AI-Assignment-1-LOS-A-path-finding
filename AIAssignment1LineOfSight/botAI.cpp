#include "botAI.h"

/**************************************************************************************************************/

/*Constructs the BotAI object*/
BotAI::BotAI(Texture * inTexture, Vec2 inPos, Vec2 inSource, int inSpriteW, int inSpriteH, int w, int h, Map* map) 
	: Creature(inTexture, inPos, inSource, inSpriteW, inSpriteH, w, h)
{
	/*initialise the path finding*/
	aStar = new AStar(map->getNumberOfXObjects(), map->getNumberOfYObjects());

	/*initialise the a* nodes*/
	for (int y = 0; y < map->getNumberOfYObjects(); y++)
	{
		for (int x = 0; x < map->getNumberOfXObjects(); x++)
		{
			/*check if the position is a wall*/
			if (map->getMapPositionType(x, y) == 'w')
			{
				/*set the node to not be safe*/
				aStar->setDangerNode(x, y);
			}
		}
	}

	/*initialise the Vec2s*/
	moveTarget = position;
	nextPosition = position;
	lastNode = position;

	/*initialise the bot to not running*/
	running = false;
}

/**************************************************************************************************************/

/*Destructs the BotAI object*/
BotAI::~BotAI()
{
}

/**************************************************************************************************************/

/*Test if the player is in sight*/
void BotAI::playerLineOfSight(Player* player, Map* map)
{
	/*if the player is in sight*/
	if (LOS::lineOfSight(position + Vec2(width * 0.5f, height * 0.5f), 
		player->getPosition() + Vec2(player->getWidth() * 0.5f, player->getHeight() * 0.5f), map))
	{
		/*if the bot is not running initialise the path finding*/
		if (!running)
		{
			/*initialise the next position*/
			nextPosition = position;

			/*get a new target*/
			moveTarget = LOS::getNewTarget(player->getPosition(), map);

			/*generate a new path*/
			aStar->findNewPath((int)(position.x / 32), (int)(position.y / 32), (int)(moveTarget.x / 32), (int)(moveTarget.y / 32));
		}
	}
}

/**************************************************************************************************************/

/*Update the next movement of the BotAI*/
void BotAI::updateMovement(Player* player, Map* map, float dt)
{
	/*check that the bot has not reached its destination*/
	if (nextPosition.x != moveTarget.x || nextPosition.y != moveTarget.y)
	{
		/*if the next node has been reached*/
		if (position.x >= nextPosition.x && position.x <= nextPosition.x + 32
			&& position.y >= nextPosition.y && position.y <= nextPosition.y + 32)
		{
			/*check if the target is still hidden from the player*/
			if (!LOS::lineOfSight(player->getPosition() + Vec2(15, 15), moveTarget + Vec2(16, 16), map))
			{
				/*set the last node value*/
				lastNode = nextPosition;
				/*set the next node value*/
				nextPosition = aStar->getNextPathNode();
			}
			/*if not regenerate a path and target*/
			else
			{
				/*get a new target*/
				moveTarget = LOS::getNewTarget(player->getPosition(), map);

				/*generate a new path*/
				aStar->findNewPath((int)(position.x / 32), (int)(position.y / 32), (int)(moveTarget.x / 32), (int)(moveTarget.y / 32));
			}
			/*set the bot to flee*/
			running = true;
		}

	}
	else
	{
		/*test if the destination has been reached*/
		if (position.x == moveTarget.x && position.y == moveTarget.y)
		{
			/*stop running*/
			running = false;
		}
	}

	/*update velocities*/
	updateMovementVelocities(dt, running);
}

/**************************************************************************************************************/

/*Update the movement velocities*/
void BotAI::updateMovementVelocities(float dt, bool check)
{
	/*if the bot should move*/
	if (check)
	{
		/*the position next frame*/
		float testX = position.x + (velocities.x * dt);
		float testY = position.y + (velocities.y * dt);

		/*if the target is to the left*/
		if (nextPosition.x < position.x)
		{
			/*if the next frame is also to the left*/
			if (nextPosition.x < testX)
			{
				/*set the velocity to go left*/
				velocities.x = -100.0f;
			}
			else
			{
				/*set the position to the next position*/
				position.x = nextPosition.x;
				velocities.x = 0.0f;
			}
		}

		/*if the target is to the right*/
		if (nextPosition.x > position.x)
		{
			/*if the next frame is also to the right*/
			if (nextPosition.x > testX)
			{
				/*set the velocity to go right*/
				velocities.x = 100.0f;
			}
			else
			{
				/*set the position to the next position*/
				position.x = nextPosition.x;
				velocities.x = 0.0f;
			}
		}

		/*if the target is to the above*/
		if (nextPosition.y < position.y)
		{
			/*if the next frame is also to the above*/
			if (nextPosition.y < testY)
			{
				/*set the velocity to go above*/
				velocities.y = -100.0f;
			}
			else
			{
				/*set the position to the next position*/
				position.y = nextPosition.y;
				velocities.y = 0.0f;
			}
		}

		/*if the target is to the bellow*/
		if (nextPosition.y > position.y)
		{
			/*if the next frame is also to the bellow*/
			if (nextPosition.y > testY)
			{
				/*set the velocity to go bellow*/
				velocities.y = 100.0f;
			}
			else
			{
				/*set the position to the next position*/
				position.y = nextPosition.y;
				velocities.y = 0.0f;
			}
		}
	}
	else
	{
		/*stop moving*/
		velocities = { 0.0f, 0.0f };
	}
}

/**************************************************************************************************************/

/*Draw the path of the BotAI from the target*/
void BotAI::drawPath(SDL_Renderer* renderer, Vec2 target)
{
	/*draw the path*/
	aStar->drawLists(renderer);

	/*creates a rectangle*/
	SDL_Rect box;

	/*set draw colour to blue*/
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);

	/*draw the target*/
	box.x = (int)moveTarget.x;
	box.y = (int)moveTarget.y;
	box.w = box.h = 32;
	SDL_RenderFillRect(renderer, &box);

	/*set draw colour to red*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);

	/*draw a line between the player and target*/
	SDL_RenderDrawLine(renderer, (int)moveTarget.x + 16, (int)moveTarget.y + 16, (int)target.x + 15, (int)target.y + 15);
}

/**************************************************************************************************************/

/*Returns the last node the bot was after*/
Vec2 BotAI::getLastNodePosition()
{
	/*return the last nodes position*/
	return lastNode;
}