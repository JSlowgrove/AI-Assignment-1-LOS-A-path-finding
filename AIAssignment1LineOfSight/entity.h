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
	/**The position of the sprite in the spritesheet*/
	Vec2 source;
	/**The dimensions of the sprite*/
	int spriteWidth, spriteHeight;
	/**The dimensions of the Entity*/
	int width, height;	
	/**A pointer to the Texture*/
	Texture* texture;
public:
	/**
	Constructs an Entity object
	@param Texture * A pointer to the texture
	@param Vec2 The position of the Entity
	@param Vec2 The position of the sprite
	@param int The sprite width
	@param int The sprite height
	@param int The Entity width
	@param int The Entity height
	*/
	Entity(Texture*, Vec2, Vec2, int, int, int, int);

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