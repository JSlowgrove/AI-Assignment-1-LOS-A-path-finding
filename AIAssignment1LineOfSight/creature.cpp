#include "creature.h"

/**************************************************************************************************************/

/*Constructs the creature object*/
Creature::Creature(Texture * inTexture, Vec2 inPos, Vec2 inSource, int inSpriteW, int inSpriteH, int w, int h)
	: Entity(inTexture, inPos, inSource, inSpriteW, inSpriteH, w, h)
{
	/*initialises the velocities*/
	velocities = { 0.0f, 0.0f };
}

/**************************************************************************************************************/

/*Destructs the creature object*/
Creature::~Creature()
{
}

/**************************************************************************************************************/

/*Updates the creature position*/
void Creature::updatePosition(float dt)
{
	/*updates the position using the velocities and dt*/
	position += (velocities * dt);
}

/**************************************************************************************************************/

/*sets the velocities*/
void Creature::setVelocities(Vec2 inVelocities)
{
	/*sets the velocities*/
	velocities = inVelocities;
}

/**************************************************************************************************************/

/*gets the velocities*/
Vec2 Creature::getVelocities()
{
	/*returns the velocities*/
	return velocities;
}