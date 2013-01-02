/*
Node and Move class represent the game search tree.
*/

#ifndef _NODE_H_
#define _NODE_H_

#include "board.h"

class Node;
/*
Player1 has Heuristics in negative and Player 2 has Heuristics in positive

if m_turn is equal to Player1 then the least Heuristics value node must be selected from the m_children 
if m_turn is equal to Player2 then the Highest Heuristics value node must be selected from the m_children
*/
typedef vector<Node*> Children;

class Node
{
public:
	Node(): m_parent(NULL),
			m_bestHeuristics(0),
			m_indexOfBestChild(-1),
			m_visited( false )
	{
	}

	Node(Board board, Turn turn) :	m_parent(NULL),
									m_bestHeuristics(0),
									m_indexOfBestChild(-1),
									m_visited( false )
	{
		m_board = board;
		m_turn  = turn;
	}

	void		setParent(Node* parent) {  m_parent = parent; }
	Node*		getParent() { return m_parent; }

	Children	getChildren() { return m_children; }
	void		setChildren( Children *children) { m_children = *children; }

	Children*	getChildrenByRef() { return &m_children; }

	Board		getBoard() { return m_board; }

	void expand( Turn player );

	Turn getTurn() { return m_turn; }

	bool		m_visited;
	int			m_bestHeuristics;
	int			m_indexOfBestChild;

private:
	Node		*m_parent;
	Children	m_children;
	Board		m_board;
	Turn		m_turn;
	
};

class Moves
{
public:
	Moves()
	{
	}

	void generateMoves(Turn turn, Node *rootNode, Children *levels, int noOfLevels);
};

#endif
