#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"
#include "creature.h"
#include "player.h"
#include "map.h"
#include "lineOfSight.h"
#include "aStar.h"

/**
@brief Creates a BotAI object that inherits Creature.
Creates a BotAI object that inherits Creature and contains the details for the BotAI.
*/
class BotAI : public Creature
{
protected:
	/**The A* pathfinding*/
	AStar* aStar;
	Vec2 moveTarget;
	Vec2 nextPosition;
	/**If the BotAI is seen by the player*/
	bool isSeen;
	/**If the BotAI is currently running*/
	bool running;

	/**
	Update the movement velocities of the BotAI
	@param float The delta time
	*/
	void updateMovementVelocities(float);

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
	@param Map * A pointer to the map
	*/
	BotAI(Texture*, Vec2, Vec2, int, int, int, int, Map*);

	/**
	Destructs the BotAI object
	*/
	~BotAI();

	/**
	Test if the player is in sight
	@param Player * A pointer to the player
	@param Map * A pointer to the map
	*/
	void playerLineOfSight(Player*, Map*);

	/**
	Update the next movement of the BotAI
	@param Player * A pointer to the player
	@param Map * A pointer to the map
	@param float The delta time
	*/
	void updateMovement(Player*, Map*, float);

	/**
	Draw the path of the BotAI if they are running from the player
	@param SDL_Renderer * A pointer to the renderer
	*/
	void drawPath(SDL_Renderer*);
};