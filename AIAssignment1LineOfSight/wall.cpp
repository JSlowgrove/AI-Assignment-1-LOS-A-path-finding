#include "wall.h"

/**************************************************************************************************************/

/*Constructs the wall object*/
Wall::Wall(Texture * inTexture, Vec2 inPos, int w, int h) : Entity(inTexture, inPos, w, h)
{
}

/**************************************************************************************************************/

/*Destructs the wall object*/
Wall::~Wall()
{
}
