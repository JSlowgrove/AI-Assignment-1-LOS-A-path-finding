#include "entity.h"

/**************************************************************************************************************/

/*Constructs the entity object*/
Entity::Entity(Texture * inTexture, Vec2 inPos, int w, int h)
{
	/*initialise variables*/
	texture = inTexture;
	position = inPos;
	width = w;
	height = h;
}

/**************************************************************************************************************/

/*Destructs the entity object*/
Entity::~Entity()
{
}

/**************************************************************************************************************/

/*Displays the entity object*/
void Entity::display(SDL_Renderer * renderer)
{
	/*display the entity*/
	texture->pushToScreen(renderer, (int)position.x, (int)position.y, width, height);
}

/**************************************************************************************************************/

/*sets the position*/
void Entity::setPosition(Vec2 inPos)
{
	/*sets the position*/
	position = inPos;
}

/**************************************************************************************************************/

/*gets the position*/
Vec2 Entity::getPosition()
{
	/*return the position*/
	return position;
}

/**************************************************************************************************************/

/*gets the width*/
int Entity::getWidth()
{
	/*return the width*/
	return width;
}

/**************************************************************************************************************/

/*gets the height*/
int Entity::getHeight()
{
	/*return the height*/
	return height;
}