#include "node.h"

void Node::expand(Turn player)
{
	unsigned int	i;
	BoardCollection m_collection;

	if ( m_board.getWinningStatePlayer1() || m_board.getWinningStatePlayer2() )
		return;

	for ( i = 0 ; i < 9 ; i++ )
	{
		if ( m_board.getValue( i) == Empty )
		{
			Board temp = m_board;
			temp.setValue( i, (BoardSquare)player);

			temp.verifyWinningState(  );

			m_collection.push_back( temp );
		}
	}

	for (i = 0; i < m_collection.size() ; i++ )
	{
		Node *newNode = new Node( m_collection[i], player );
		newNode->setParent(this);
		m_children.push_back( newNode );
	}
}

void Moves::generateMoves(Turn turn, Node *rootNode, Children *levels, int noOfLevels)
{
	unsigned int i = 0 , j = 0, k = 0;
	
	rootNode->expand( turn );
	levels[0] = rootNode->getChildren();

	for ( i =1 ; i < noOfLevels ; i++ )
	{
		if ( turn == Player1Turn )
			turn = Player2Turn;
		else
			turn = Player1Turn;

		for ( j = 0 ; j < levels[i - 1].size() ; j++)
		{
			levels[i - 1][j]->expand(turn);
			Children tempChildren = levels[i - 1][j]->getChildren();

			for ( k = 0 ; k < tempChildren.size() ; k++ )
			{
				levels[i].push_back( tempChildren[k] );
			}
		}

		if ( levels[i].size() == 0 )
			break;
	}
}
