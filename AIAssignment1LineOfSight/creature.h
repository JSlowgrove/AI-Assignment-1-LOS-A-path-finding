#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"
#include "entity.h"
#include "map.h"

/**
@brief Creates a Creature object that inherits Entity.
Creates a Creature object that inherits Entity and contains the details for the Creature.
*/
class Creature : public Entity
{
protected:
	/**The Creature velocities*/
	Vec2 velocities;
	/**The min and max tiles that the creature is on*/
	int minX, maxX, minY, maxY;

	/**
	Tests if the Creature collides with a Wall for a certain direction and performs an act upon the result
	@param Map * A pointer to the Map
	@param float The delta time
	@param float The velocity from the axis to be tested
	@param float The position from the axis to be tested
	@param int The minimum i index
	@param int The maximum i index
	@param int The minimum j index
	@param int The maximum j index
	@param char The axis being checked
	@param float Returns the new velocity.
	*/
	float collision(Map *, float, float, float, int, int, int, int, char);

	/**
	Display tiles being tested for collision
	@param SDL_Renderer * A pointer to the renderer
	@param Map * A pointer to the Map
	@param int The minimum i index
	@param int The maximum i index
	@param int The minimum j index
	@param int The maximum j index
	*/
	void displayCollisionTest(SDL_Renderer*, Map *, int, int, int, int);

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

	/**
	Display the tiles that the Creature occupies
	@param SDL_Renderer * A pointer to the renderer
	@param Map * A pointer to the Map
	*/
	void displayTiles(SDL_Renderer*, Map*);

	/**
	Tests if the Creature collides with a Wall and performs an act upon the result
	@param Map * A pointer to the Map
	@param float The delta time
	*/
	void collisionUpdate(Map *, float);

	/**
	Tests if the Creature collides with an Entity and performs an act upon the result
	@param Map * A pointer to the Entity
	@param float The delta time
	*/
	void collisionUpdate(Entity *, float);
};