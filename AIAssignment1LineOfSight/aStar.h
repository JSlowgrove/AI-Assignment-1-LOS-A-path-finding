#pragma once

#include <vector>
#include "node.h"

/**
@brief Creates an object for A* path finding
*/
class AStar
{
private:
	/**The arrays of Nodes*/
	std::vector<std::vector<Node*>> nodes;
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	/**The number of nodes*/
	int xNodes;
	int yNodes;
	/**The current node index*/
	int currentX;
	int currentY;

	/**
	Check the surrounding nodes
	@param int The parent node x index value
	@param int The parent node y index value
	*/
	void checkNodes(int parentX, int parentY);

	/**
	Find the next node
	@param int The value of the heuristic
	*/
	void findNextNode(int h);

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

	/**
	Finds a new path to follow
	@param int The start x index value
	@param int The start y index value
	@param int The end x index value
	@param int The end y index value
	*/
	void findNewPath(int startX, int startY, int endX, int endY);
};