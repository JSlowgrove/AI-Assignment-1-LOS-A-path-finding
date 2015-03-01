#include "botA.h"

/**************************************************************************************************************/

/*Constructs the BotA object*/
BotA::BotA(Texture * inTexture, Vec2 inPos, int w, int h, Map* map) : BotAI(inTexture, inPos, Vec2(0.0f, 0.0f), 70, 70, w, h, map)
{
}

/**************************************************************************************************************/

/*Destructs the BotA object*/
BotA::~BotA()
{
}