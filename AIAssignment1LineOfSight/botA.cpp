#include "botA.h"

/**************************************************************************************************************/

/*Constructs the BotA object*/
BotA::BotA(Texture * inTexture, Vec2 inPos, int w, int h) : BotAI(inTexture, inPos, Vec2(0.0f, 0.0f), 70, 70, w, h)
{
}

/**************************************************************************************************************/

/*Destructs the BotA object*/
BotA::~BotA()
{
}