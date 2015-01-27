#include "wall.h"

/**************************************************************************************************************/

/*Constructs the wall object*/
Wall::Wall(Texture * inTexture, Vec2 inPos, int w, int h) : Entity(inTexture, inPos, Vec2(210.0f, 0.0f), 70, 70, w, h)
{
}

/**************************************************************************************************************/

/*Destructs the wall object*/
Wall::~Wall()
{
}
