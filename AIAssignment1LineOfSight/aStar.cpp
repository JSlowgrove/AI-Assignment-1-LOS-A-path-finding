#include "aStar.h"

/**************************************************************************************************************/

/*Constructs the A* object*/
AStar::AStar(int xNodes, int yNodes)
{
	/*initialise variables*/
	this->xNodes = xNodes;
	this->yNodes = yNodes;

	/*initialise arrays*/
	for (int x = 0; x < xNodes; x++)
	{
		nodes.resize(x + 1);
		for (int y = 0; y < yNodes; y++)
		{
			/*add a new node [x][y]*/
			nodes[x].push_back(new Node(x, y));
		}
	}
}


/**************************************************************************************************************/

/*Destructs the A* object*/
AStar::~AStar()
{
	/*delete pointers*/
	for (int x = 0; x < xNodes; x++)
	{
		for (int y = 0; y < yNodes; y++)
		{
			delete nodes[x][y];
		}
	}
}

/**************************************************************************************************************/

/*Sets the node to not be safe*/
void AStar::setDangerNode(int nodeXIndex, int nodeYIndex)
{
	/*set the node to not be safe*/
	nodes[nodeXIndex][nodeYIndex]->setSafeNode(false);
}

/**************************************************************************************************************/

/*finds a new path to follow*/
void AStar::findNewPath(int startX, int startY, int endX, int endY)
{
	/*reset listed information and start and stop nodes*/
	for (int x = 0; x < xNodes; x++)
	{
		for (int y = 0; y < yNodes; y++)
		{
			nodes[x][y]->setListed(false);
			nodes[x][y]->setStartNode(false);
			nodes[x][y]->setEndNode(false);
		}
	}

	/*reset open closed list and the best path*/
	openList.clear();
	closedList.clear();
	bestPath.clear();

	/*initialise start and end nodes*/
	nodes[startX][startY]->setStartNode(true);
	nodes[endX][endY]->setEndNode(true);

	/*push back the start node to the open list and set it as listed*/
	openList.push_back(*nodes[startX][startY]);
	nodes[startX][startY]->setListed(true);

	/*initialise the start, current and end node index*/
	this->startX = currentX = startX;
	this->startY = currentY = startY;
	this->endX = endX;
	this->endY = endY;

	/*initialise the check*/
	bool reachedEnd = false;

	/*the number of loops*/
	int loopIndex = 0;

	/*loop until the end has been reached*/
	while (!reachedEnd)
	{
		/*add the parent and child nodes to an open list if they are safe
		and set there parent node and cost*/
		checkNodes(currentX, currentY);

		/*find the next node*/
		findNextNode();

		/*check if the end has been reached*/
		if (closedList.back().getEndNode())
		{
			/*leave the loop*/
			reachedEnd = true;
			std::cout << "path found" << std::endl;
		}

		/*if too many loops give up looking for a path*/
		if (loopIndex > 1300)
		{
			/*leave the loop*/
			reachedEnd = true;
			std::cout << "too many loops, give up on a* test" << std::endl;
		}

		/*increase loop index*/
		loopIndex++;
	}

	/*find the best path*/
	findBestPath();
}

/**************************************************************************************************************/

/*checks the surrounding nodes*/
void AStar::checkNodes(int parentX, int parentY)
{
	/*top left test*/
	//nodeTest(parentX, parentY, parentX - 1, parentY - 1, 14);

	/*top middle test*/
	nodeTest(parentX, parentY, parentX, parentY - 1, 10);

	/*top right test*/
	//nodeTest(parentX, parentY, parentX + 1, parentY - 1, 14);

	/*middle left test*/
	nodeTest(parentX, parentY, parentX - 1, parentY, 10);

	/*middle right test*/
	nodeTest(parentX, parentY, parentX + 1, parentY, 10);

	/*bottom left test*/
	//nodeTest(parentX, parentY, parentX - 1, parentY + 1, 14);

	/*bottom middle test*/
	nodeTest(parentX, parentY, parentX, parentY + 1, 10);

	/*bottom right test*/
	//nodeTest(parentX, parentY, parentX + 1, parentY + 1, 14);
}

/**************************************************************************************************************/

/*test the node*/
void AStar::nodeTest(int parentX, int parentY, int testX, int testY, int cost)
{
	/*the node being tested*/
	Node currentNode = *nodes[testX][testY];

	/*test if the test node is on the screen*/
	if (testX < nodes.size() && testX >= 0 && testY < nodes[0].size() && testY >= 0)
	{
		/*test if the node is safe to move on and is not listed*/
		if (currentNode.getSafeNode() && !currentNode.getListed())
		{
			/*set the node to be listed*/
			nodes[testX][testY]->setListed(true);

			/*set the parent node of the node*/
			currentNode.setParentIndex(parentX, parentY);

			/*set the cost to the cost of the parent node plus the newly added cost*/
			currentNode.setCostNode(nodes[parentX][parentY]->getCostNode() + cost);

			/*work out the heuristic using the Manhattan method
			(total number of squares moved horizontally and vertically to end)*/
			int h = (abs(testX - endX) + abs(testY - endY)) * cost;

			/*set the fScore of the node*/
			currentNode.setFScoreNode(h + currentNode.getCostNode());

			/*push the node*/
			openList.push_back(currentNode);
		}
	}
}

/**************************************************************************************************************/

/*finds the next node*/
void AStar::findNextNode()
{
	/*the current closest node index*/
	unsigned int closestIndex = 0;

	/*loop through the open list of nodes*/
	for (unsigned int i = 1; i < openList.size(); i++)
	{
		/*if the current fScore is lower set the current to the current index*/
		if (openList[closestIndex].getFScoreNode() >= openList[i].getFScoreNode())
		{
			closestIndex = i;
		}
	}

	/*set the current x and y*/
	currentX = openList[closestIndex].getXIndex();
	currentY = openList[closestIndex].getYIndex();

	/*move the initial node to the closed list*/
	closedList.push_back(openList[closestIndex]);

	/*remove the node from the open list*/
	openList.erase(openList.begin() + closestIndex);
}

/**************************************************************************************************************/

/*gets the next path node position*/
Vec2 AStar::getNextPathNode()
{
	/*initialise and set the position of the next node to the index of the back of the closed list*/
	Vec2 nextNodePosition = { (float)(bestPath.back().getXIndex() * 32), (float)(bestPath.back().getYIndex() * 32) };
	
	/*remove the node at the front of the list*/
	bestPath.erase(bestPath.begin() + (bestPath.size() - 1));

	/*return the next node position*/
	return nextNodePosition;
}

/**************************************************************************************************************/

/*gets the best path*/
void AStar::findBestPath()
{
	std::vector<Node> fullPath = closedList;

	int parentX = fullPath.back().getXIndex();
	int parentY = fullPath.back().getYIndex();
	
	bool home = false;
	while (!home)
	{
		Node currentNode = fullPath.back();
		fullPath.pop_back();
		if (parentX == currentNode.getXIndex() && parentY == currentNode.getYIndex())
		{
			bestPath.push_back(currentNode);
			if (currentNode.getStartNode())
			{
				home = true;
			}
			else
			{
				parentX = currentNode.getParentXIndex();
				parentY = currentNode.getParentYIndex();
			}
		}
	}
}

/**************************************************************************************************************/

/*displays the path*/
void AStar::drawLists(SDL_Renderer* renderer)
{
	/*set draw colour to white*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/*creates a rectangle*/
	SDL_Rect box;

	for (auto node : openList)
	{
		/*update the box for the tile*/
		box.x = node.getXIndex() * 32;
		box.y = node.getYIndex() * 32;
		box.w = box.h = 32;

		/*draw the tiles outline*/
		SDL_RenderDrawRect(renderer, &box);
	}

	/*set draw colour to black*/
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

	for (auto node : closedList)
	{
		/*update the box for the tile*/
		box.x = node.getXIndex() * 32;
		box.y = node.getYIndex() * 32;
		box.w = box.h = 32;

		/*draw the tiles outline*/
		SDL_RenderDrawRect(renderer, &box);
	}

	/*set draw colour to cyan*/
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0x00);

	/*draw the best path*/
	for (auto node : bestPath)
	{
		/*update the box for the tile*/
		box.x = node.getXIndex() * 32;
		box.y = node.getYIndex() * 32;
		box.w = box.h = 32;

		/*draw the tiles outline*/
		SDL_RenderFillRect(renderer, &box);
	}
}