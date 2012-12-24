/*
The classes in this file represent moves and generate moves.
*/

#ifndef _NODE_H_

#include "board.h"

class Node;

typedef vector<Node> Children;

class Node
{
public:
	Node() : m_parent(NULL)
	{
	}

	Node(Board board) : m_parent(NULL)
	{
		m_board = board;
	}

	void		setParent(Node* parent) {  m_parent = parent; }
	Node*		getParent() { return m_parent; }

	Children	getChildren() { return m_children; }
	Board		getBoard() { return m_board; }

	void expand( Player player );

private:
	Node		*m_parent;
	Children	m_children;
	Board		m_board;
};

class Moves
{
public:
	Moves()
	{
	}

	void generateMoves(Player turn, Node *rootNode, Children *levels, int noOfLevels);
};

#endif
