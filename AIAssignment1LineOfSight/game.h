#pragma once

#include <SDL.h>
#include "state.h"
#include "stateManager.h"
#include "texture.h"
#include "audio.h"
#include "map.h"
#include "wall.h"
#include "player.h"
#include "botA.h"
#include "botB.h"
#include "lineOfSight.h"
#include "aStar.h"

/**
@brief Creates a Game object that inherits State
Creates a Game object that inherits State and runs the Game.
*/
class Game : public State
{
private:
	/**Texture pointers*/
	Texture* background;
	Texture* spritesheet;
	/**Entity pointers*/
	Map* map;
	Player* player;
	BotA* botA;
	BotB* botB;
	AStar* aStar;
	/*developer mode*/
	bool developer;
public:
	/**
	Constructs a Game object
	@param StateManager * a pointer to the StateManager
	@param SDL_Renderer * a pointer to the renderer
	@param int the screen width
	@param int the screen height
	*/
	Game(StateManager *, SDL_Renderer *, int, int);

	/**
	Destructs a Game object
	*/
	~Game();

	/**
	Handles the Game input
	@returns bool if false the quit the Game State
	*/
	bool input();

	/**
	A function to update the Game
	A function to update the Game to allow the Game to run
	@param float the delta time
	*/
	void update(float deltaTime);

	/**
	A function to draw to the screen
	*/
	void draw();
};