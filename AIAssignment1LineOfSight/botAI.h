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
protected:
public:
	/**
	Constructs a BotAI object
	@param Texture * A pointer to the Texture
	@param Vec2 The position of the BotAI
	@param Vec2 The position of the sprite
	@param int The sprite width
	@param int The sprite height
	@param int The BotAI width
	@param int The BotAI height
	*/
	BotAI(Texture*, Vec2, Vec2, int, int, int, int);

	/**
	Destructs the BotAI object
	*/
	~BotAI();
};