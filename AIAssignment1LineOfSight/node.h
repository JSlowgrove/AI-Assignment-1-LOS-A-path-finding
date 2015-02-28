#pragma once

/**
@brief Creates a Node object
Creates a Node object for use with path finding
*/
class Node
{
private:
	/*the index of the parent node*/
	int parentNodeXIndex;
	int parentNodeYIndex;
	/*the index of the node*/
	int nodeXIndex;
	int nodeYIndex;
	/*boolean values to if they are a specific node*/
	bool startNode;
	bool endNode;
	/*is the node safe to walk on*/
	bool safe;
	/*the cost to move to the node*/
	int cost;
	/*the f score of the node*/
	int fScore;
	/*boolean values for if the node is on a list*/
	bool listed;
public:
	/**
	Constructs a Node object
	@param int The Node x index
	@param int The Node y index
	*/
	Node(int nodeXIndex, int nodeYIndex);

	/**
	Destructs a Game object
	*/
	~Node();

	/**
	Setter # Set the parentNode index
	@param int The X index of the parentNode
	@param int The Y index of the parentNode
	*/
	void setParentIndex(int parentNodeXIndex, int parentNodeYIndex);

	/**
	Getter # Get the parentNode X index
	@return int The X index of the parentNode
	*/
	int getParentXIndex();

	/**
	Getter # Get the parentNode Y index
	@return int The Y index of the parentNode
	*/
	int getParentYIndex();

	/**
	Setter # Set the node
	@param bool The setting of the node
	*/
	void setStartNode(bool startNode);

	/**
	Getter # Get If the node is a startNode
	@return bool If the node is a startNode
	*/
	bool getStartNode();

	/**
	Setter # Set the node
	@param bool The setting of the node
	*/
	void setEndNode(bool endNode);

	/**
	Getter # Get If the node is an endNode
	@return bool If the node is an endNode
	*/
	bool getEndNode();

	/**
	Setter # Set the node
	@param bool The setting of the node
	*/
	void setSafeNode(bool safe);

	/**
	Getter # Get If the node is safe
	@return bool If the node is safe
	*/
	bool getSafeNode();

	/**
	Setter # Set the cost
	@param int The cost to move to the node
	*/
	void setCostNode(int cost);

	/**
	Getter # Get the cost
	@return int The cost to move to the node
	*/
	int getCostNode();

	/**
	Setter # Set the fScore
	@param bool The fScore to of the node
	*/
	void setFScoreNode(int fScore);

	/**
	Getter # Get the fScore
	@return int The fScore to of the node
	*/
	int getFScoreNode();

	/**
	Getter # Get the x index
	@return int The x index of the node
	*/
	int getXIndex();

	/**
	Getter # Get the y index
	@return int The y index of the node
	*/
	int getYIndex();

	/**
	Setter # Set the value of listed
	@param bool If the node is listed
	*/
	void setListed(bool listed);

	/**
	Getter # Get the value of listed
	@return bool If the node is listed
	*/
	bool getListed();
};