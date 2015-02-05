#include "botAI.h"

/**************************************************************************************************************/

/*Constructs the BotAI object*/
BotAI::BotAI(Texture * inTexture, Vec2 inPos, Vec2 inSource, int inSpriteW, int inSpriteH, int w, int h) 
	: Creature(inTexture, inPos, inSource, inSpriteW, inSpriteH, w, h)
{
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
		/*tmp movement*/
		velocities = { 100.0f, 100.0f };
	}
	else
	{
		/*tmp movement*/
		velocities = { 0.0f, 0.0f };
	}
}