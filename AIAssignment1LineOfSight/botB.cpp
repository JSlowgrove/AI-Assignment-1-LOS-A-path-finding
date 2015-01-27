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