#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"

/**
@brief Creates an Entity object that contains the details for the Entity.
*/
class Entity
{
protected:
	/**The position of the Entity*/
	Vec2 position;
	/**The dimensions of the Entity*/
	int width;
	int height;	
	/**A pointer to the Texture*/
	Texture* texture;
public:
	/**
	Constructs an Entity object
	@param SDL_Renderer * A pointer to the renderer
	@param Vec2 The position of the Entity
	@param int The screen width
	@param int The screen height
	*/
	Entity(Texture*, Vec2, int, int);

	/**
	Destructs the Entity object
	*/
	~Entity();

	/**
	Displays the Entity
	@param SLD_Renderer * A pointer to the renderer
	*/
	void display(SDL_Renderer*);

	/**
	Setter # Sets the position
	@param Vec2 The new position
	*/
	void setPosition(Vec2);

	/**
	Getter # Gets the position
	@returns Vec2 The position
	*/
	Vec2 getPosition();

	/**
	Getter # Gets the width
	@returns int The width
	*/
	int getWidth();

	/**
	Getter # Gets the height
	@returns int The height
	*/
	int getHeight();
};