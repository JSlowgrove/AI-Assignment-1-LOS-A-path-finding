#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"
#include "botAI.h"
#include "botA.h"

/**
@brief Creates a BotB object that inherits BotAI.
Creates a BotB object that inherits BotAI and contains the details for the BotA.
*/
class BotB : public BotAI
{
private:
	/**If the bot is following*/
	bool following;
	/**A pointer to BotA*/
	BotA* botA;

	/**
	The movements of the BotB when following
	@param Creature * A pointer to the creature
	@param Map * A pointer to the map
	@param float The delta time
	*/
	void updateMoveFollow(Creature*, Map*, float);

public:
	/**
	Constructs an BotB object
	@param Texture * a pointer to the Texture
	@param Vec2 the position of the Player
	@param int the width of the BotB
	@param int the height of the BotB
	@param Map * A pointer to the map
	*/
	BotB(Texture*, Vec2, int, int, Map*);

	/**
	Destructs an BotA object
	*/
	~BotB();

	/**
	Test if the Player is in sight and if BotA should be followed
	@param Player * A pointer to the Player
	@param BotA * A pointer to the BotA
	@param Map * A pointer to the map
	*/
	void playerLineOfSight(Player*, BotA*, Map*);

	/**
	Update the next movement of the BotB
	@param BotA * A pointer to the Player
	@param Map * A pointer to the map
	@param float The delta time
	*/
	void updateMovement(Player* , Map*, float);
};