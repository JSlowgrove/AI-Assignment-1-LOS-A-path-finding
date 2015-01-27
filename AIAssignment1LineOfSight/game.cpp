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
		case SDL_QUIT: /*If player closes the window, end the game loop*/

			return false;
			break;

		case SDL_KEYDOWN:

			switch (incomingEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE: /*If Escape is pressed, end the game loop*/

				return false;
				break;
			}
		}
	}
	return true;
}

/**************************************************************************************************************/

/*updates the game*/
void Game::update(float dt)
{
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

	/*display other entities*/
	player->display(renderer);
	botA->display(renderer);
	botB->display(renderer);

	/*display renderer*/
	SDL_RenderPresent(renderer);
}