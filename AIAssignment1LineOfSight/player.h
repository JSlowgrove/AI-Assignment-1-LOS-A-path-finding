#pragma once

#include <SDL.h>
#include "texture.h"
#include "vec2.h"
#include "creature.h"

/**
@brief Creates a Player object that inherits Creature.
Creates a Player object that inherits Creature and contains the details for the Player.
*/
class Player : public Creature
{
private:
	/**Input commands*/
	bool up, down, left, right;
public:
	/**
	Constructs a Player object
	@param Texture * a pointer to the Texture
	@param Vec2 the position of the Player
	@param int the width of the Player
	@param int the height of the Player
	*/
	Player(Texture*, Vec2, int, int);

	/**
	Destructs the Player object
	*/
	~Player();

	/**
	Setter # Input command - Up
	@param bool The new state of the command
	*/
	void commandUp(bool);

	/**
	Setter # Input command - Down
	@param bool The new state of the command
	*/
	void commandDown(bool);

	/**
	Setter # Input command - Left
	@param bool The new state of the command
	*/
	void commandLeft(bool);

	/**
	Setter # Input command - Right
	@param bool The new state of the command
	*/
	void commandRight(bool);

	/**
	Handle the current set of commands
	*/
	void handleCommands();
};