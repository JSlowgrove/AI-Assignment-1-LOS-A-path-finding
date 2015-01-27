#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"
#include "botAI.h"

/**
@brief Creates a BotA object that inherits BotAI.
Creates a BotA object that inherits BotAI and contains the details for the BotA.
*/
class BotA : public BotAI
{
private:
public:
	/**
	Constructs an BotA object
	@param Texture * a pointer to the Texture
	@param Vec2 the position of the Player
	@param int the width of the BotA
	@param int the height of the BotA
	*/
	BotA(Texture*, Vec2, int, int);

	/**
	Destructs an BotA object
	*/
	~BotA();
};