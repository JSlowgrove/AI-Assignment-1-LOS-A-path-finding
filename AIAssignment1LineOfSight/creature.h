#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"
#include "entity.h"

/**
@brief Creates a Creature object that inherits Entity.
Creates a Creature object that inherits Entity and contains the details for the Creature.
*/
class Creature : public Entity
{
protected:
	/**The Creature velocities*/
	Vec2 velocities;
public:
	/**
	Constructs a Creature object
	@param Texture * A pointer to the Texture
	@param Vec2 The position of the Creature
	@param Vec2 The position of the sprite
	@param int The sprite width
	@param int The sprite height
	@param int The Creature width
	@param int The Creature height
	*/
	Creature(Texture*, Vec2, Vec2, int, int, int, int);

	/**
	Destructs the Creature object
	*/
	~Creature();

	/**
	Updates the Creature position using the velocities and the delta time
	@param float The delta time
	*/
	void updatePosition(float);

	/**
	Setter # Sets the velocities
	@param Vec2 The new velocities
	*/
	void setVelocities(Vec2);

	/**
	Getter # Gets the velocities
	@returns Vec2 The velocities
	*/
	Vec2 getVelocities();
};