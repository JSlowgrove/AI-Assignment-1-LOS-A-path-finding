#include "botB.h"

/**************************************************************************************************************/

/*Constructs the BotB object*/
BotB::BotB(Texture * inTexture, Vec2 inPos, int w, int h) : BotAI(inTexture, inPos, Vec2(70.0f, 0.0f), 70, 70, w, h)
{
}

/**************************************************************************************************************/

/*Destructs the BotB object*/
BotB::~BotB()
{
}

/**************************************************************************************************************/

/*Test if botA is in sight*/
void BotB::botALineOfSight(Player* player, BotA* bot, Map* map)
{
	/*if the bot is in sight and the player is not*/
	if (LOS::lineOfSight(position + Vec2(width * 0.5f, height * 0.5f),
		bot->getPosition() + Vec2(bot->getWidth() * 0.5f, bot->getHeight() * 0.5f), map)
		&& !LOS::lineOfSight(position + Vec2(width * 0.5f, height * 0.5f),
		player->getPosition() + Vec2(player->getWidth() * 0.5f, player->getHeight() * 0.5f), map))
	{
		/*tmp movement*/
		velocities = { -100.0f, -100.0f };
	}
}