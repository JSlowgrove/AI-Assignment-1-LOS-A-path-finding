#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"
#include "entity.h"

/**
@brief Creates an Creature object that inherits Entity.
Creates an Creature object that inherits Entity and contains the details for the Creature.
*/
class Creature : public Entity
{
protected:
	/**The Creature velocities*/
	Vec2 velocities;
public:
	/**
	Constructs a Creature object
	@param SDL_Renderer * A pointer to the renderer
	@param Vec2 The position of the Creature
	@param int The screen width
	@param int The screen height
	*/
	Creature(Texture*, Vec2, int, int);

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