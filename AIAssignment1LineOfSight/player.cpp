#include "player.h"

/**************************************************************************************************************/

/*Constructs the player object*/
Player::Player(Texture * inTexture, Vec2 inPos, int w, int h) : Creature(inTexture, inPos, Vec2(140.0f, 0.0f), 70, 70, w, h)
{
}

/**************************************************************************************************************/

/*Destructs the player object*/
Player::~Player()
{
}

/**************************************************************************************************************/

/*sets state of the up command*/
void Player::commandUp(bool command)
{
	/*sets the state of the command*/
	up = command;
}

/**************************************************************************************************************/

/*sets state of the down command*/
void Player::commandDown(bool command)
{
	/*sets the state of the command*/
	down = command;
}

/**************************************************************************************************************/

/*sets state of the left command*/
void Player::commandLeft(bool command)
{
	/*sets the state of the command*/
	left = command;
}

/**************************************************************************************************************/

/*sets state of the right command*/
void Player::commandRight(bool command)
{
	/*sets the state of the command*/
	right = command;
}