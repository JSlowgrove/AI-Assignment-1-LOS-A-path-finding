#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"
#include "entity.h"

/**
@brief Creates a Wall object that inherits Entity.
Creates a Wall object that inherits Entity and contains the details for the Wall.
*/
class Wall : public Entity
{
private:	
public:
	/**
	Constructs a Wall object
	@param Texture * A pointer to the Texture
	@param Vec2 The position of the Wall
	@param int the width of the Wall
	@param int the height of the Wall
	*/
	Wall(Texture*, Vec2, int, int);

	/**
	Destructs the Creature object
	*/
	~Wall();
};