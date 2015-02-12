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
	/*boolean values to if they are a specific node*/
	bool startNode;
	bool endNode;
	/*is the node safe to walk on*/
	bool safe;
public:
	/**
	Constructs a Node object
	*/
	Node();

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
};