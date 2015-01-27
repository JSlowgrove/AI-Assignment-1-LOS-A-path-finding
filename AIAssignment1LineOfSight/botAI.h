#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"
#include "creature.h"

/**
@brief Creates an BotAI object that inherits Creature.
Creates an BotAI object that inherits Creature and contains the details for the BotAI.
*/
class BotAI : public Creature
{
private:
public:
	/**
	Constructs an BotAI object
	@param SDL_Renderer * a pointer to the renderer
	@param Vec2 the position of the Player
	@param int the screen width
	@param int the screen height
	*/
	BotAI(Texture*, Vec2, int, int);

	/**
	Destructs an BotAI object
	*/
	~BotAI();
};