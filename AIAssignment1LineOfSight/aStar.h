#pragma once

#include <iostream>
#include <vector>
#include "node.h"
#include "SDL.h"
#include "vec2.h"

/**
@brief Creates an object for A* path finding
Made using help from http://www.policyalmanac.org/games/aStarTutorial.htm
*/
class AStar
{
private:
	/**The arrays of Nodes*/
	std::vector<std::vector<Node*>> nodes;
	std::vector<Node> openList;
	std::vector<Node> closedList;
	std::vector<Node> bestPath;
	/**The number of nodes*/
	int xNodes;
	int yNodes;
	/**The current node index*/
	int currentX;
	int currentY;
	/**The end node index*/
	int endX;
	int endY;
	/**The start node index*/
	int startX;
	int startY;

	/**
	Check the surrounding nodes
	@param int The parent node x index value
	@param int The parent node y index value
	*/
	void checkNodes(int parentX, int parentY);

	/**
	Test the node for the open list setup
	@param int The parent x index value
	@param int The parent y index value
	@param int The test x index value
	@param int The test y index value
	@param int The cost to add to the node
	*/
	void nodeTest(int parentX, int parentY, int testX, int testY, int cost);

	/**
	Find the next node
	*/
	void findNextNode();

	/**
	Find the best path
	*/
	void findBestPath();

public:
	/**
	Constructs an AStar object
	@param int The number of nodes in a row
	@param int The number of rows in the map
	*/
	AStar(int xNodes, int yNodes);

	/**
	Destructs an AStar object
	*/
	~AStar();

	void setDangerNode(int nodeXIndex, int nodeYIndex);

	/**
	Finds a new path to follow
	@param int The start x index value
	@param int The start y index value
	@param int The end x index value
	@param int The end y index value
	*/
	void findNewPath(int startX, int startY, int endX, int endY);

	/**
	Returns the position of the next node in the path
	@returns Vec2 Node position
	*/
	Vec2 getNextPathNode();

	/**
	Displays the open and closed lists
	@param SDL_Renderer* A pointer to the renderer
	*/
	void drawLists(SDL_Renderer* renderer);
};