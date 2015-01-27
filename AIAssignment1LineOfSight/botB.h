#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"
#include "botAI.h"

/**
@brief Creates a BotB object that inherits BotAI.
Creates a BotB object that inherits BotAI and contains the details for the BotA.
*/
class BotB : public BotAI
{
private:
public:
	/**
	Constructs an BotB object
	@param Texture * a pointer to the Texture
	@param Vec2 the position of the Player
	@param int the width of the BotB
	@param int the height of the BotB
	*/
	BotB(Texture*, Vec2, int, int);

	/**
	Destructs an BotA object
	*/
	~BotB();
};