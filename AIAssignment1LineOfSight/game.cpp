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
	botA = new BotA(spritesheet, map->getInitialBotA(), 30, 30, map);
	botB = new BotB(spritesheet, map->getInitialBotB(), 30, 30, map);

	/*initialise developer mode options*/
	developer = true;
	showCollisions = true;
	showLOS = true;
	showAStar = true;

	/*initialise the first run boolean*/
	firstRun = true;

	/*initialise the music boolean*/
	playMusic = true;

	/*initialise random seed*/
	srand((unsigned int)time(NULL));
	
	/*initialise the text (font from http://www.dafont.com/code.font)*/
	text.push_back(new Text("Developer Mode: ", "font/CODE_Bold.ttf", renderer, 255, 255, 0));
	text.push_back(new Text("Music: ", "font/CODE_Bold.ttf", renderer, 255, 255, 0));
	text.push_back(new Text("Show Collision Tests: ", "font/CODE_Bold.ttf", renderer, 255, 255, 0));
	text.push_back(new Text("Show LOS Tests: ", "font/CODE_Bold.ttf", renderer, 255, 255, 0));
	text.push_back(new Text("Show A Star Tests: ", "font/CODE_Bold.ttf", renderer, 255, 255, 0));
	text.push_back(new Text("ON", "font/CODE_Bold.ttf", renderer, 0, 255, 0));
	text.push_back(new Text("OFF", "font/CODE_Bold.ttf", renderer, 255, 0, 0));
	text.push_back(new Text("Bot A Running: ", "font/CODE_Bold.ttf", renderer, 255, 255, 0));
	text.push_back(new Text("Bot B Running: ", "font/CODE_Bold.ttf", renderer, 255, 255, 0));
	text.push_back(new Text("Bot B Following: ", "font/CODE_Bold.ttf", renderer, 255, 255, 0));
	text.push_back(new Text("TRUE", "font/CODE_Bold.ttf", renderer, 0, 255, 0));
	text.push_back(new Text("FALSE", "font/CODE_Bold.ttf", renderer, 255, 0, 0));

	/*initialise and start the music*/
	music = new Audio("aud/Cipher.ogg", true);
	music->startAudio();
}

/**************************************************************************************************************/

/*Destructs the game object*/
Game::~Game()
{
	/*stop music*/
	music->stopAudio();
	/*delete pointers*/
	for (unsigned int i = 0; i < text.size(); i++)
	{
		delete text[i];
	}
	delete music;
	delete background;
	delete spritesheet;
	delete map;
	delete player;
	delete botA;
	delete botB;
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
		case SDL_QUIT: /*If player closes the window end the game loop*/
			return false;
			break;

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

			case SDLK_TAB:/*if tab is pressed switch developer mode*/
				developer = !developer;
				break;

			case SDLK_1:/*if tab is pressed toggle displaying collisions*/
				showCollisions = !showCollisions;
				break;

			case SDLK_2:/*if tab is pressed toggle displaying LOS*/
				showLOS = !showLOS;
				break;

			case SDLK_3:/*if tab is pressed toggle displaying aStar*/
				showAStar = !showAStar;
				break;

			case SDLK_m:/*if m is pressed toggle playing music*/
				playMusic = !playMusic;
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
	/*check if music should play*/
	if (playMusic)
	{
		/*make sure the music is playing*/
		music->startAudio();
	}
	else
	{
		/*stop the music*/
		music->stopAudio();
	}

	/*if not first loop run the updates*/
	if (!firstRun)
	{
		/*handle the player input*/
		player->handleCommands();

		/*update the player collisions*/
		player->collisionUpdate(map, dt);

		/*test the bots for player line of sight*/
		botA->playerLineOfSight(player, map);
		botB->playerLineOfSight(player, botA, map);

		/*update the bot movements*/
		botA->updateMovement(player, map, dt);
		botB->updateMovement(player, map, dt);

		/*update the bot collisions*/
		botA->collisionUpdate(map, dt);
		botB->collisionUpdate(map, dt);

		/*update creature collisions*/
		/*botA->collisionUpdate(botB, dt);
		botA->collisionUpdate(player, dt);
		botB->collisionUpdate(botA, dt);
		botB->collisionUpdate(player, dt);
		player->collisionUpdate(botA, dt);
		player->collisionUpdate(botB, dt);*/

		/*update the player*/
		player->updatePosition(dt);

		/*update the bots*/
		botA->updatePosition(dt);
		botB->updatePosition(dt);
	}
	else
	{
		firstRun = false;
	}
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

	/*developer display*/
	if (developer)
	{
		/*if show LOS is toggled on*/
		if (showLOS)
		{	
			/*set draw colour to yellow*/
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);

			/*draw a line between the player and bot a*/
			SDL_RenderDrawLine(renderer,
				(int)botA->getPosition().x + (int)(botA->getWidth()*0.5f),
				(int)botA->getPosition().y + (int)(botA->getHeight()*0.5f),
				(int)player->getPosition().x + (int)(player->getWidth()*0.5f),
				(int)player->getPosition().y + (int)(player->getHeight()*0.5f));

			/*draw a line between the player and bot b*/
			SDL_RenderDrawLine(renderer,
				(int)botB->getPosition().x + (int)(botB->getWidth()*0.5f),
				(int)botB->getPosition().y + (int)(botB->getHeight()*0.5f),
				(int)player->getPosition().x + (int)(player->getWidth()*0.5f),
				(int)player->getPosition().y + (int)(player->getHeight()*0.5f));

			/*draw a line between the player and bot a*/
			SDL_RenderDrawLine(renderer,
				(int)botA->getPosition().x + (int)(botA->getWidth()*0.5f),
				(int)botA->getPosition().y + (int)(botA->getHeight()*0.5f),
				(int)botB->getPosition().x + (int)(botB->getWidth()*0.5f),
				(int)botB->getPosition().y + (int)(botB->getHeight()*0.5f));

			/*draw the line of sight calculations*/
			LOS::drawLineOfSight(botA->getPosition() + Vec2(botA->getWidth()*0.5f, botA->getHeight()*0.5f),
				player->getPosition() + Vec2(player->getWidth()*0.5f, player->getHeight()*0.5f), map, renderer);
			LOS::drawLineOfSight(botB->getPosition() + Vec2(botB->getWidth()*0.5f, botB->getHeight()*0.5f),
				player->getPosition() + Vec2(player->getWidth()*0.5f, player->getHeight()*0.5f), map, renderer);
			LOS::drawLineOfSight(botA->getPosition() + Vec2(botA->getWidth()*0.5f, botA->getHeight()*0.5f),
				botB->getPosition() + Vec2(botB->getWidth()*0.5f, botB->getHeight()*0.5f), map, renderer);
		}

		/*if show collisions is toggled on*/
		if (showCollisions)
		{
			/*draw the intersection tiles with the creatures*/
			player->displayTiles(renderer, map);
			botA->displayTiles(renderer, map);
			botB->displayTiles(renderer, map);
		}

		/*if show aStar is toggled on*/
		if (showAStar)
		{
			/*draw the a* paths*/
			botA->drawPath(renderer, player->getPosition());
			botB->drawPath(renderer, player->getPosition());
			botB->drawPath(renderer, botA->getPosition());
		}
	}

	/*display other entities*/
	player->display(renderer);
	botA->display(renderer);
	botB->display(renderer);

	/*draw the text*/
	drawText();

	/*display renderer*/
	SDL_RenderPresent(renderer);
}

/**************************************************************************************************************/

/*draws the text*/
void Game::drawText()
{
	/*display default text*/
	text[0]->pushToScreen(renderer, 10, 10, 100, 10);/*Developer Mode*/
	text[1]->pushToScreen(renderer, 10, 20, 50, 10);/*Music*/

	/*check if music should is on*/
	if (playMusic)
	{
		/*display on*/
		text[5]->pushToScreen(renderer, 170, 20, 30, 10);
	}
	else
	{
		/*display off*/
		text[6]->pushToScreen(renderer, 170, 20, 30, 10);
	}

	/*developer display*/
	if (developer)
	{
		/*display development text*/
		text[2]->pushToScreen(renderer, 10, 30, 150, 10);/*show collisions*/
		text[3]->pushToScreen(renderer, 10, 40, 100, 10);/*show LOS*/
		text[4]->pushToScreen(renderer, 10, 50, 100, 10);/*show A Star*/
		text[7]->pushToScreen(renderer, 10, 60, 100, 10);/*show Bot A Running*/
		text[8]->pushToScreen(renderer, 10, 70, 100, 10);/*show Bot B Running*/
		text[9]->pushToScreen(renderer, 10, 80, 100, 10);/*show Bot B Following*/

		/*display Bot A running state*/
		if (botA->getRunning())
		{
			/*display true*/
			text[10]->pushToScreen(renderer, 170, 60, 50, 10);
		}
		else
		{
			/*display false*/
			text[11]->pushToScreen(renderer, 170, 60, 50, 10);
		}

		/*display Bot B running state*/
		if (botB->getRunning())
		{
			/*display true*/
			text[10]->pushToScreen(renderer, 170, 70, 50, 10);
		}
		else
		{
			/*display false*/
			text[11]->pushToScreen(renderer, 170, 70, 50, 10);
		}

		/*display Bot B following state*/
		if (botB->getFollowing())
		{
			/*display true*/
			text[10]->pushToScreen(renderer, 170, 80, 50, 10);
		}
		else
		{
			/*display false*/
			text[11]->pushToScreen(renderer, 170, 80, 50, 10);
		}

		/*development mode on text*/
		text[5]->pushToScreen(renderer, 170, 10, 30, 10);

		/*if show LOS is toggled on*/
		if (showLOS)
		{
			/*show LOS on text*/
			text[5]->pushToScreen(renderer, 170, 40, 30, 10);
		}
		else
		{
			/*show LOS off text*/
			text[6]->pushToScreen(renderer, 170, 40, 30, 10);
		}

		/*if show collisions is toggled on*/
		if (showCollisions)
		{
			/*show collisions on text*/
			text[5]->pushToScreen(renderer, 170, 30, 30, 10);
		}
		else
		{
			/*show collisions off text*/
			text[6]->pushToScreen(renderer, 170, 30, 30, 10);
		}

		/*if show aStar is toggled on*/
		if (showAStar)
		{
			/*show aStar on text*/
			text[5]->pushToScreen(renderer, 170, 50, 30, 10);
		}
		else
		{
			/*show aStar off text*/
			text[6]->pushToScreen(renderer, 170, 50, 30, 10);
		}
	}
	else
	{
		/*development mode off text*/
		text[6]->pushToScreen(renderer, 170, 10, 30, 10);
	}
}