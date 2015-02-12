#include "aStar.h"

/**************************************************************************************************************/

/*Constructs the A* object*/
AStar::AStar(int xNodes, int yNodes)
{
	/*initialise variables*/
	this->xNodes = xNodes;
	this->yNodes = yNodes;

	/*initialise arrays*/
	for (int i = 0; i < yNodes; i++)
	{
		nodes.resize(i + 1);
		for (int j = 0; j < xNodes; j++)
		{
			nodes[i].push_back(new Node());
		}
	}
}


/**************************************************************************************************************/

/*Destructs the A* object*/
AStar::~AStar()
{
	/*delete pointers*/
	for (int i = 0; i < yNodes; i++)
	{
		for (int j = 0; j < xNodes; j++)
		{
			delete nodes[i][j];
		}
	}
}

/**************************************************************************************************************/

/*finds a new path to follow*/
void AStar::findNewPath(int startX, int startY, int endX, int endY)
{
	/*initialise start and end nodes*/
	nodes[startX][startY]->setStartNode(true);
	nodes[endX][endY]->setEndNode(true);

	/*add the parent and child nodes to an open list if they are safe
	and set there parent node*/
	checkNodes(startX, startY);
}

/**************************************************************************************************************/

/*checks the surrounding nodes*/
void AStar::checkNodes(int parentX, int parentY)
{
	/*add the start node to the open list*/
	openList.push_back(nodes[parentX][parentY]);

	/*top left*/
	if (nodes[parentX - 1][parentY - 1]->getSafeNode())
	{
		openList.push_back(nodes[parentX - 1][parentY - 1]);
		nodes[parentX - 1][parentY - 1]->setParentIndex(parentX, parentY);
	}

	/*top middle*/
	if (nodes[parentX][parentY - 1]->getSafeNode())
	{
		openList.push_back(nodes[parentX][parentY - 1]);
		nodes[parentX][parentY - 1]->setParentIndex(parentX, parentY);
	}

	/*top right*/
	if (nodes[parentX + 1][parentY - 1]->getSafeNode())
	{
		openList.push_back(nodes[parentX + 1][parentY - 1]);
		nodes[parentX + 1][parentY - 1]->setParentIndex(parentX, parentY);
	}

	/*middle left*/
	if (nodes[parentX - 1][parentY]->getSafeNode())
	{
		openList.push_back(nodes[parentX - 1][parentY]);
		nodes[parentX - 1][parentY]->setParentIndex(parentX, parentY);
	}

	/*middle right*/
	if (nodes[parentX + 1][parentY]->getSafeNode())
	{
		openList.push_back(nodes[parentX + 1][parentY]);
		nodes[parentX + 1][parentY]->setParentIndex(parentX, parentY);
	}

	/*bottom left*/
	if (nodes[parentX - 1][parentY + 1]->getSafeNode())
	{
		openList.push_back(nodes[parentX - 1][parentY + 1]);
		nodes[parentX - 1][parentY + 1]->setParentIndex(parentX, parentY);
	}

	/*bottom middle*/
	if (nodes[parentX][parentY + 1]->getSafeNode())
	{
		openList.push_back(nodes[parentX][parentY + 1]);
		nodes[parentX][parentY + 1]->setParentIndex(parentX, parentY);
	}

	/*bottom right*/
	if (nodes[parentX + 1][parentY + 1]->getSafeNode())
	{
		openList.push_back(nodes[parentX + 1][parentY + 1]);
		nodes[parentX + 1][parentY + 1]->setParentIndex(parentX, parentY);
	}

	/*move the initial node to the closed list*/
	closedList.push_back(openList[openList.size() - 9]);
	openList.erase(openList.begin() + (openList.size() - 9));
}