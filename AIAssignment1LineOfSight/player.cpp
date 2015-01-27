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

/**************************************************************************************************************/

/*handles the commands*/
void Player::handleCommands()
{
	/*if the player should go up*/
	if (up && !down)
	{
		/*set the y velocity to -100*/
		velocities.y = -100.0f;
	}
	/*if the player should go down*/
	else if (down && !up)
	{
		/*set the y velocity to 100*/
		velocities.y = 100.0f;
	}
	/*if the player should stop on the y axis*/
	else
	{
		/*set the y velocity to 0*/
		velocities.y = 0.0f;
	}

	/*if the player should go left*/
	if (left && !right)
	{
		/*set the x velocity to -100*/
		velocities.x = -100.0f;
	}
	/*if the player should go right*/
	else if (right && !left)
	{
		/*set the x velocity to 100*/
		velocities.x = 100.0f;
	}
	/*if the player should stop on the x axis*/
	else
	{
		/*set the x velocity to 0*/
		velocities.x = 0.0f;
	}
}