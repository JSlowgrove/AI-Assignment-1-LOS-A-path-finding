#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"
#include "entity.h"

/**
@brief Creates an Wall object that inherits Entity.
Creates an Wall object that inherits Entity and contains the details for the Wall.
*/
class Wall : public Entity
{
private:	
public:
	/**
	Constructs a Wall object
	@param SDL_Renderer * A pointer to the renderer
	@param Vec2 The position of the Wall
	@param int The screen width
	@param int The screen height
	*/
	Wall(Texture*, Vec2, int, int);

	/**
	Destructs the Creature object
	*/
	~Wall();
};