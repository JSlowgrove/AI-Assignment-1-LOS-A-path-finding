#include "map.h"

/**************************************************************************************************************/

/*Constructs the map object*/
Map::Map(Texture* inSheet, std::string fileName)
{
	/*initialise the spritesheet*/
	spritesheet = inSheet;
	/*load the map*/
	loadMap(fileName);
}

/**************************************************************************************************************/

/*Destructs the map object*/
Map::~Map()
{
	/*delete pointers*/
	for (unsigned int i = 0; i < map.size(); i++)
	{
		for (unsigned int j = 0; j < map[i].size(); j++)
		{
			delete map[i][j];
		}
	}
	for (unsigned int i = 0; i < walls.size(); i++)
	{
		delete walls[i];
	}
}

/**************************************************************************************************************/

/*Load the map*/
void Map::loadMap(std::string fileName)
{
	/*open the file using a ifstream*/
	std::ifstream file(fileName);
	/*creates a vector of strings for the lines in the file*/
	std::vector<std::string> line;

	/*if the file successfully opens*/
	if (file.is_open())
	{
		/*file read in*/
		int i = -1;
		std::string currentLine;
		/*while there are still lines to be read in from the file*/
		while (getline(file, currentLine))
		{
			i++;
			line.resize(i + 1);
			line[i] = currentLine;
		}
		file.close();

		/*resize the 2D vector*/
		map.resize(line.size());
		for (unsigned int i = 0; i < line.size(); i++)
		{
			/*every 2nd loaded char is an entity*/
			map[i].resize(line[0].size());
		}

		/*Loop for the number of lines in the line array*/
		for (unsigned int i = 0; i < line.size(); i++)
		{
			/*loop for the number of characters in a single line*/
			for (unsigned int j = 0; j < line[i].size(); j++)
			{
				/*loads in the type of the next map object*/
				switch (line[i][j])
					{
					/*if x then blank*/
					case 'x':
						map[i][j] = new id('x', 0);
						break;
					/*if w then add a new wall*/
					case 'w':
						map[i][j] = new id('w', walls.size());
						walls.push_back(new Wall(spritesheet, Vec2((float)j * 32 , (float)i * 32), 32, 32));
						break;
					/*if p then initialise the player position*/
					case 'p':
						player = { (float)j * 32, (float)i * 32 };
						/*shift the player to center of tile*/
						player += {1.0f, 1.0f};
						/*set the tile to blank*/
						map[i][j] = new id('x', 0);
						break;
					/*if a then initialise the botA position*/
					case 'a':
						botA = { (float)j * 32, (float)i * 32 };
						/*shift the bot to center of tile*/
						botA += {1.0f, 1.0f};
						/*set the tile to blank*/
						map[i][j] = new id('x', 0);
						break;
					/*if b then initialise the botB position*/
					case 'b':
						botB = { (float)j * 32, (float)i * 32 };
						/*shift the bot to center of tile*/
						botB += {1.0f, 1.0f};
						/*set the tile to blank*/
						map[i][j] = new id('x', 0);
						break;
					}

			}
		}
	}
	/*if the file could be opened then output error message*/
	else
	{
		std::cout << "Unable to open file";
	}
}

/**************************************************************************************************************/

/*gets the index from the map*/
int Map::getMapPositionIndex(int x, int y)
{
	/*return the index*/
	return map[y][x]->index;
}

/**************************************************************************************************************/

/*gets the type from the map*/
char Map::getMapPositionType(int x, int y)
{
	/*return the type*/
	return map[y][x]->type;
}

/**************************************************************************************************************/

/*gets the wall from the index position*/
Wall* Map::getWall(int i)
{
	/*return the wall*/
	return walls[i];
}

/**************************************************************************************************************/

/*gets the number of walls*/
int Map::getNumberOfWalls()
{
	/*return the number of walls*/
	return (int)walls.size();
}

/**************************************************************************************************************/

/*gets the initial player position*/
Vec2 Map::getInitialPlayer()
{
	/*return the initial player position*/
	return player;
}

/**************************************************************************************************************/

/*gets the initial botA position*/
Vec2 Map::getInitialBotA()
{
	/*return the initial bot position*/
	return botA;
}

/**************************************************************************************************************/

/*gets the initial botB position*/
Vec2 Map::getInitialBotB()
{
	/*return the initial bot position*/
	return botB;
}