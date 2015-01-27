#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "texture.h"
#include "wall.h"

/**
@brief Creates a Map object
*/
class Map
{
private:
	/**A structure for use with the Map*/
	struct id
	{
		/*The type of the Entity - x = Blank, w = Wall*/
		char type;
		/*The index of the Entity within its array*/
		int index;

		/**
		Constructs an id
		Constructs the id setting the values to the input values
		@param char The inputed type
		@param int The inputed index
		*/
		id(char inType, int inIndex)
		{
			type = inType;
			index = inIndex;
		}
	};

	/**2D Map of Entity objects*/
	std::vector<std::vector<id*>> map;
	/**Entity pointers*/
	std::vector<Wall*> walls;
	/*Vec2 positions of the Creature starts*/
	Vec2 player, botA, botB;
	/*A pointer to the spritesheet Texture*/
	Texture* spritesheet;

	/**
	Loads the Map
	@param std::string The file location
	*/
	void loadMap(std::string);

public:
	/**
	Constructs a Map object
	@param Texture* A pointer to the spritesheet Texture
	@param std::string The file location
	*/
	Map(Texture*, std::string);

	/**
	Destructs a Map object
	*/
	~Map();

	/**
	Getter # Gets the index
	Gets the index stored in the Map at the given position
	@param int The x index of the map
	@param int The y index of the map
	@returns int The index
	*/
	int getMapPositionIndex(int, int);

	/**
	Getter # Gets the type
	Gets the type stored in the Map at the given position
	@param int The x index of the map
	@param int The y index of the map
	@returns char The type
	*/
	char getMapPositionType(int, int);

	/**
	Getter # Gets the Wall
	Gets the Wall stored in the array at the given index
	@param int The index of the Wall
	@returns Wall * A pointer to the Wall
	*/
	Wall* getWall(int);

	/**
	Getter # Gets the number of Wall objects
	@returns int The number of Wall objects
	*/
	int getNumberOfWalls();

	/**
	Getter # Gets the initial Player position
	@returns Vec2 The initial Player position
	*/
	Vec2 getInitialPlayer();

	/**
	Getter # Gets the initial BotA position
	@returns Vec2 The initial BotA position
	*/
	Vec2 getInitialBotA();

	/**
	Getter # Gets the initial BotB position
	@returns Vec2 The initial BotB position
	*/
	Vec2 getInitialBotB();
};