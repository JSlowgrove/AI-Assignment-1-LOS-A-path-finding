#include "creature.h"

/**************************************************************************************************************/

/*Constructs the creature object*/
Creature::Creature(Texture * inTexture, Vec2 inPos, Vec2 inSource, int inSpriteW, int inSpriteH, int w, int h)
	: Entity(inTexture, inPos, inSource, inSpriteW, inSpriteH, w, h)
{
	/*initialises the velocities*/
	velocities = { 0.0f, 0.0f };
	/*initialise the min and max tiles*/
	minX = maxX = (int)((inPos.x - 1) / 32);
	minY = maxY = (int)((inPos.y - 1) / 32);
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

	/*update the tiles*/
	minX = (int)(position.x / 32);
	maxX = (int)((position.x + width) / 32);
	minY = (int)(position.y / 32);
	maxY = (int)((position.y + height) / 32);
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

/**************************************************************************************************************/

/*displays the tiles the creature occupies*/
void Creature::displayTiles(SDL_Renderer* renderer)
{
	/*creates a rectangle using the tiles*/
	SDL_Rect box;
	box.x = minX * 32;
	box.y = minY * 32;
	box.w = 32 + ((maxX - minX) * 32);
	box.h = 32 + ((maxY - minY) * 32);

	/*set the draw colour to green*/
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);

	/*draw the tiles outline*/
	SDL_RenderDrawRect(renderer, &box);
}