#include "aStar.h"

/**************************************************************************************************************/

/*Constructs the A* object*/
AStar::AStar(int xNodes, int yNodes, SDL_Renderer* renderer)
{
	/*initialise variables*/
	this->xNodes = xNodes;
	this->yNodes = yNodes;
	this->renderer = renderer;

	/*initialise arrays*/
	for (int i = 0; i < xNodes; i++)
	{
		nodes.resize(i + 1);
		for (int j = 0; j < yNodes; j++)
		{
			nodes[i].push_back(new Node(i,j));
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

	/*initialise the current node index*/
	currentX = startX;
	currentY = startY;

	/*initialise the check*/
	bool reachedEnd = false;
	
	/*loop until the end has been reached*/
	while (!reachedEnd)
	{
		/*add the parent and child nodes to an open list if they are safe
		and set there parent node and cost*/
		checkNodes(currentX, currentY);

		/*work out the heuristic using the Manhattan method
		(total number of squares moved horizontally and vertically to end)*/
		int h = abs(endY - currentY) + abs(endX - currentX);

		/*find the next node*/
		findNextNode(h);

		/*check if the end has been reached*/
		if (currentX == endX && currentY == endY)
		{
			/*leave the loop*/
			reachedEnd = true;
		}
	}

}

/**************************************************************************************************************/

/*checks the surrounding nodes*/
void AStar::checkNodes(int parentX, int parentY)
{

/*creates a rectangle*/
SDL_Rect box;

/*top left*/
if (nodes[parentX - 1][parentY - 1]->getSafeNode() && parentX != 0 && parentY !=0)
{
	openList.push_back(nodes[parentX - 1][parentY - 1]);
	nodes[parentX - 1][parentY - 1]->setParentIndex(parentX, parentY);
	/*set the cost to the cost of the parent node plus 14*/
	nodes[parentX - 1][parentY - 1]->setCostNode(nodes[parentX][parentY]->getCostNode() + 14);
	
	/*set the draw colour to white*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/*update the box for the test area*/
	box.x = (parentX - 1) * 32;
	box.y = (parentY - 1) * 32;
	box.w = box.h = 32;

	/*draw the test area outline*/
	SDL_RenderDrawRect(renderer, &box);
}

/*top middle*/
if (nodes[parentX][parentY - 1]->getSafeNode() && parentX != 0 && parentY != 0)
{
	openList.push_back(nodes[parentX][parentY - 1]);
	nodes[parentX][parentY - 1]->setParentIndex(parentX, parentY);
	/*set the cost to the cost of the parent node plus 10*/
	nodes[parentX][parentY - 1]->setCostNode(nodes[parentX][parentY]->getCostNode() + 10);

	/*set the draw colour to white*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/*update the box for the test area*/
	box.x = (parentX) * 32;
	box.y = (parentY - 1) * 32;
	box.w = box.h = 32;

	/*draw the test area outline*/
	SDL_RenderDrawRect(renderer, &box);
}

/*top right*/
if (nodes[parentX + 1][parentY - 1]->getSafeNode() && parentX != 0 && parentY != 0)
{
	openList.push_back(nodes[parentX + 1][parentY - 1]);
	nodes[parentX + 1][parentY - 1]->setParentIndex(parentX, parentY);
	/*set the cost to the cost of the parent node plus 14*/
	nodes[parentX + 1][parentY - 1]->setCostNode(nodes[parentX][parentY]->getCostNode() + 14);

	/*set the draw colour to white*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/*update the box for the test area*/
	box.x = (parentX + 1) * 32;
	box.y = (parentY - 1) * 32;
	box.w = box.h = 32;

	/*draw the test area outline*/
	SDL_RenderDrawRect(renderer, &box);
}

/*middle left*/
if (nodes[parentX - 1][parentY]->getSafeNode() && parentX != 0 && parentY != 0)
{
	openList.push_back(nodes[parentX - 1][parentY]);
	nodes[parentX - 1][parentY]->setParentIndex(parentX, parentY);
	/*set the cost to the cost of the parent node plus 10*/
	nodes[parentX - 1][parentY]->setCostNode(nodes[parentX][parentY]->getCostNode() + 10);

	/*set the draw colour to white*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/*update the box for the test area*/
	box.x = (parentX - 1) * 32;
	box.y = (parentY) * 32;
	box.w = box.h = 32;

	/*draw the test area outline*/
	SDL_RenderDrawRect(renderer, &box);
}

/*middle right*/
if (nodes[parentX + 1][parentY]->getSafeNode() && parentX != 0 && parentY != 0)
{
	openList.push_back(nodes[parentX + 1][parentY]);
	nodes[parentX + 1][parentY]->setParentIndex(parentX, parentY);
	/*set the cost to the cost of the parent node plus 10*/
	nodes[parentX + 1][parentY]->setCostNode(nodes[parentX][parentY]->getCostNode() + 10);

	/*set the draw colour to white*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/*update the box for the test area*/
	box.x = (parentX + 1) * 32;
	box.y = (parentY) * 32;
	box.w = box.h = 32;

	/*draw the test area outline*/
	SDL_RenderDrawRect(renderer, &box);
}

/*bottom left*/
if (nodes[parentX - 1][parentY + 1]->getSafeNode() && parentX != 0 && parentY != 0)
{
	openList.push_back(nodes[parentX - 1][parentY + 1]);
	nodes[parentX - 1][parentY + 1]->setParentIndex(parentX, parentY);
	/*set the cost to the cost of the parent node plus 14*/
	nodes[parentX - 1][parentY + 1]->setCostNode(nodes[parentX][parentY]->getCostNode() + 14);

	/*set the draw colour to white*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/*update the box for the test area*/
	box.x = (parentX - 1) * 32;
	box.y = (parentY + 1) * 32;
	box.w = box.h = 32;

	/*draw the test area outline*/
	SDL_RenderDrawRect(renderer, &box);
}

/*bottom middle*/
if (nodes[parentX][parentY + 1]->getSafeNode() && parentX != 0 && parentY != 0)
{
	openList.push_back(nodes[parentX][parentY + 1]);
	nodes[parentX][parentY + 1]->setParentIndex(parentX, parentY);
	/*set the cost to the cost of the parent node plus 10*/
	nodes[parentX][parentY + 1]->setCostNode(nodes[parentX][parentY]->getCostNode() + 10);

	/*set the draw colour to white*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/*update the box for the test area*/
	box.x = (parentX) * 32;
	box.y = (parentY + 1) * 32;
	box.w = box.h = 32;

	/*draw the test area outline*/
	SDL_RenderDrawRect(renderer, &box);
}

/*bottom right*/
if (nodes[parentX + 1][parentY + 1]->getSafeNode() && parentX != 0 && parentY != 0)
{
	openList.push_back(nodes[parentX + 1][parentY + 1]);
	nodes[parentX + 1][parentY + 1]->setParentIndex(parentX, parentY);
	/*set the cost to the cost of the parent node plus 14*/
	nodes[parentX + 1][parentY + 1]->setCostNode(nodes[parentX][parentY]->getCostNode() + 14);

	/*set the draw colour to white*/
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	/*update the box for the test area*/
	box.x = (parentX + 1) * 32;
	box.y = (parentY + 1) * 32;
	box.w = box.h = 32;

	/*draw the test area outline*/
	SDL_RenderDrawRect(renderer, &box);
}

/*move the initial node to the closed list*/
closedList.push_back(nodes[parentX][parentY]);

/*set the draw colour to red*/
SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

/*update the box for the test area*/
box.x = (parentX) * 32;
box.y = (parentY) * 32;
box.w = box.h = 32;

/*draw the test area outline*/
SDL_RenderFillRect(renderer, &box);
}


/**************************************************************************************************************/

/*finds the next node*/
void AStar::findNextNode(int h)
{
	/*loop through the open list of nodes*/
	for (unsigned int i = 0; i < openList.size(); i++)
	{
		/*set the fScore of the node*/
		openList[i]->setFScoreNode(h + openList[i]->getCostNode());
	}

	/*the current closest node index*/
	int current = 0;

	/*loop through the open list of nodes*/
	for (unsigned int i = 1; i < openList.size(); i++)
	{
		/*if the current fScore is lower set the current to the current index*/
		if (openList[current]->getFScoreNode() > openList[i]->getFScoreNode())
		{
			current = i;
		}
	}

	/*set the current x and y*/
	currentX = openList[current]->getXIndex();
	currentY = openList[current]->getYIndex();

	/*remove the node from the open list*/
	openList.erase(openList.begin() + current);
}