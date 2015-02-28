#include "node.h"

/**************************************************************************************************************/

/*Constructs the node object*/
Node::Node(int nodeXIndex, int nodeYIndex)
{
	/*initialise the booleans*/
	startNode = false;
	endNode = false;
	listed = false;
	safe = true;

	/*initialise the variables*/
	this->nodeXIndex = nodeXIndex;
	this->nodeYIndex = nodeYIndex;
	parentNodeXIndex = 0;
	parentNodeYIndex = 0;
	cost = 0;
	fScore = 0;
}


/**************************************************************************************************************/

/*Destructs the node object*/
Node::~Node()
{
}

/**************************************************************************************************************/

/*set the parent node index*/
void Node::setParentIndex(int parentNodeXIndex, int parentNodeYIndex)
{
	/*set the variables to the input*/
	this->parentNodeXIndex = parentNodeXIndex;
	this->parentNodeYIndex = parentNodeYIndex;
}

/**************************************************************************************************************/

/*get the parent node x index*/
int Node::getParentXIndex()
{
	/*return the x parent node index*/
	return parentNodeXIndex;
}

/**************************************************************************************************************/

/*get the parent node y index*/
int Node::getParentYIndex()
{
	/*return the y parent node index*/
	return parentNodeYIndex;
}

/**************************************************************************************************************/

/*set the startNode*/
void Node::setStartNode(bool startNode)
{
	/*set the node*/
	this->startNode = startNode;
}

/**************************************************************************************************************/

/*get if the node is a startNode*/
bool Node::getStartNode()
{
	/*return startNode*/
	return startNode;
}

/**************************************************************************************************************/

/*set the endNode*/
void Node::setEndNode(bool endNode)
{
	/*set the node*/
	this->endNode = endNode;
}

/**************************************************************************************************************/

/*get if the node is an endNode*/
bool Node::getEndNode()
{
	/*return endNode*/
	return endNode;
}

/**************************************************************************************************************/

/*set the safe*/
void Node::setSafeNode(bool safe)
{
	/*set the node*/
	this->safe = safe;
}

/**************************************************************************************************************/

/*get if the node is an safe*/
bool Node::getSafeNode()
{
	/*return safeNode*/
	return safe;
}

/**************************************************************************************************************/

/*set the cost*/
void Node::setCostNode(int cost)
{
	/*set the node cost*/
	this->cost = cost;
}

/**************************************************************************************************************/

/*get the cost*/
int Node::getCostNode()
{
	/*return the node cost*/
	return cost;
}

/**************************************************************************************************************/

/*set the fScore*/
void Node::setFScoreNode(int fScore)
{
	/*set the node fScore*/
	this->fScore = fScore;
}

/**************************************************************************************************************/

/*get the fScore*/
int Node::getFScoreNode()
{
	/*return the node fScore*/
	return fScore;
}

/**************************************************************************************************************/

/*get the x index*/
int Node::getXIndex()
{
	/*return the node x index*/
	return nodeXIndex;
}

/**************************************************************************************************************/

/*get the y index*/
int Node::getYIndex()
{
	/*return the node y index*/
	return nodeYIndex;
}

/**************************************************************************************************************/

/*set the listed*/
void Node::setListed(bool listed)
{
	/*set the node*/
	this->listed = listed;
}

/**************************************************************************************************************/

/*get if the node is listed*/
bool Node::getListed()
{
	/*return listed*/
	return listed;
}