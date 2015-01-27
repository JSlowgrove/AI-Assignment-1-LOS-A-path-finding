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