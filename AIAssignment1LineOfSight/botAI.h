#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"
#include "creature.h"

/**
@brief Creates a BotAI object that inherits Creature.
Creates a BotAI object that inherits Creature and contains the details for the BotAI.
*/
class BotAI : public Creature
{
private:
public:
	/**
	Constructs a BotAI object
	@param SDL_Renderer * A pointer to the renderer
	@param Vec2 The position of the Player
	@param int The screen width
	@param int The screen height
	*/
	BotAI(Texture*, Vec2, int, int);

	/**
	Destructs the BotAI object
	*/
	~BotAI();
};