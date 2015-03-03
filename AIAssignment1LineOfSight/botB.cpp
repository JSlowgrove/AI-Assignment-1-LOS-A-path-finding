#include "botB.h"

/**************************************************************************************************************/

/*Constructs the BotB object*/
BotB::BotB(Texture * inTexture, Vec2 inPos, int w, int h, Map* map) : BotAI(inTexture, inPos, Vec2(70.0f, 0.0f), 70, 70, w, h, map)
{
	/*initialise the bot to not follow*/
	following = false;
}

/**************************************************************************************************************/

/*Destructs the BotB object*/
BotB::~BotB()
{
}

/**************************************************************************************************************/

/*Test if the player is in sight*/
void BotB::playerLineOfSight(Player* player, BotA* botA, Map* map)
{
	/*if the player is in sight*/
	if (LOS::lineOfSight(position + Vec2(width * 0.5f, height * 0.5f),
		player->getPosition() + Vec2(player->getWidth() * 0.5f, player->getHeight() * 0.5f), map))
	{
		/*Stop the bot from following*/
		following = false;

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
	else
	{
		/*if the other bot is in sight*/
		if (LOS::lineOfSight(position + Vec2(width * 0.5f, height * 0.5f),
			botA->getPosition() + Vec2(botA->getWidth() * 0.5f, botA->getHeight() * 0.5f), map))
		{
			/*if the bot is not following initialise the path finding*/
			if (!following)
			{
				/*initialise the next position*/
				nextPosition = position;

				/*get a new target*/
				moveTarget = botA->getLastNodePosition();

				/*generate a new path*/
				aStar->findNewPath((int)(position.x / 32), (int)(position.y / 32), (int)(moveTarget.x / 32), (int)(moveTarget.y / 32));

				/*start following*/
				following = true;
			}
		}
	}
}

/**************************************************************************************************************/

/*Update the next movement of the BotB*/
void BotB::updateMovement(BotA* bot, Player* player, Map* map, float dt)
{
	/*is the bot following*/
	if (following)
	{
		/*check that the bot has not reached its destination*/
		if (nextPosition.x != moveTarget.x || nextPosition.y != moveTarget.y)
		{
			/*if the next node has been reached*/
			if (position.x >= nextPosition.x && position.x <= nextPosition.x + 32
				&& position.y >= nextPosition.y && position.y <= nextPosition.y + 32)
			{
				/*set the last node value*/
				lastNode = nextPosition;
				/*set the next node value*/
				nextPosition = aStar->getNextPathNode();
			}

		}
		else
		{
			/*test if the destination has been reached*/
			if (position.x == moveTarget.x && position.y == moveTarget.y)
			{
				/*stop following*/
				following = false;
			}
		}
	}
	else
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
	}
	/*update velocities*/
	updateMovementVelocities(dt);
	

}