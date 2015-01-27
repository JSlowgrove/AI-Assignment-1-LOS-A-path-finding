#include "game.h"

/**************************************************************************************************************/

/*Constructs the game object*/
Game::Game(StateManager* inStateManager, SDL_Renderer* inRenderer, int inWidth, int inHeight) 
	: State(inStateManager, inRenderer, inWidth, inHeight)
{
	/*initialise the textures*/
	background = new Texture("img/background.png", renderer);
	spritesheet = new Texture("img/spritesheet70x70.png", renderer);
	
	/*initialise the entities*/
	map = new Map(spritesheet, "txt/map.txt");
	player = new Player(spritesheet, map->getInitialPlayer(), 30, 30);
	botA = new BotA(spritesheet, map->getInitialBotA(), 30, 30);
	botB = new BotB(spritesheet, map->getInitialBotB(), 30, 30);
}

/**************************************************************************************************************/

/*Destructs the game object*/
Game::~Game()
{
	
}

/**************************************************************************************************************/

/*handles inputs*/
bool Game::input()
{
	/*Check for user input*/
	SDL_Event incomingEvent;
	while (SDL_PollEvent(&incomingEvent))
	{
		switch (incomingEvent.type)
		{
		case SDL_KEYDOWN:

			switch (incomingEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE: /*If Escape is pressed, end the game loop*/

				return false;
				break;

			case SDLK_UP: /*If up or w is pressed*/
			case SDLK_w:
				player->commandUp(true);
				break;

			case SDLK_DOWN:/*If down or s is pressed*/
			case SDLK_s:
				player->commandDown(true);
				break;

			case SDLK_LEFT:/*If left or a is pressed*/
			case SDLK_a:
				player->commandLeft(true);
				break;

			case SDLK_RIGHT:/*If right or d is pressed*/
			case SDLK_d:
				player->commandRight(true);
				break;
			}
			break;

		case SDL_KEYUP:
			switch (incomingEvent.key.keysym.sym)
			{
			case SDLK_UP: /*If up or w is released*/
			case SDLK_w:
				player->commandUp(false);
				break;

			case SDLK_DOWN:/*If down or s is released*/
			case SDLK_s:
				player->commandDown(false);
				break;

			case SDLK_LEFT:/*If left or a is released*/
			case SDLK_a:
				player->commandLeft(false);
				break;

			case SDLK_RIGHT:/*If right or d is released*/
			case SDLK_d:
				player->commandRight(false);
				break;
			}
			break;
		}
	}
	return true;
}

/**************************************************************************************************************/

/*updates the game*/
void Game::update(float dt)
{
	/*handle the player input*/
	player->handleCommands();

	/*update the player*/
	player->updatePosition(dt);
}

/**************************************************************************************************************/

/*draws the game*/
void Game::draw()
{
	/*set draw colour to white*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/*Clear the entire screen to the set colour*/
	SDL_RenderClear(renderer);

	/*display the background image*/
	background->pushToScreen(renderer, 0, 0);

	/*display the walls*/
	for (int i = 0; i < map->getNumberOfWalls(); i++)
	{
		map->getWall(i)->display(renderer);
	}

	/*set draw colour to yellow*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);

	/*draw a line between the player and bot a*/
	SDL_RenderDrawLine(renderer, 
		(int)botA->getPosition().x + (botA->getWidth()*0.5f), 
		(int)botA->getPosition().y + (botA->getHeight()*0.5f), 
		(int)player->getPosition().x + (player->getWidth()*0.5f), 
		(int)player->getPosition().y + (player->getHeight()*0.5f));

	/*draw the intersection tiles with the creatures*/
	player->displayTiles(renderer);
	botA->displayTiles(renderer);
	botB->displayTiles(renderer);

	/*display other entities*/
	player->display(renderer);
	botA->display(renderer);
	botB->display(renderer);

	/*display renderer*/
	SDL_RenderPresent(renderer);
}