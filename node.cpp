#include "node.h"

void Node::expand( Player player )
{
	unsigned int	i, j;
	BoardCollection m_collection;

	if ( m_board.getWinningStatePlayer1() || m_board.getWinningStatePlayer2() )
		return;

	for ( i = 0 ; i < 3 ; i++ )
	{
		for ( j = 0 ; j < 3 ; j++ )
		{
			if ( m_board.getValue( i, j) == 0 )
			{
				Board temp = m_board;
				temp.setValue( i, j, player);

				temp.verifyWinningState();

				m_collection.push_back( temp );
			}
		}
	}

	for (i = 0; i < m_collection.size() ; i++ )
	{
		Node newNode( m_collection[i] );
		newNode.setParent(this);
		m_children.push_back( newNode );
	}
}

void Moves::generateMoves(Player turn, Node *rootNode, Children *levels, int noOfLevels)
{
	unsigned int i = 0 , j = 0, k = 0;
	
	rootNode->expand( turn );
	levels[0] = rootNode->getChildren();

	for ( i =1 ; i < noOfLevels ; i++ )
	{
		if ( turn == Player1 )
			turn = Player2;
		else
			turn = Player1;

		for ( j = 0 ; j < levels[i - 1].size() ; j++)
		{
			levels[i - 1][j].expand(turn);
			Children tempChildren = levels[i - 1][j].getChildren();

			for ( k = 0 ; k < tempChildren.size() ; k++ )
			{
				levels[i].push_back( tempChildren[k] );
			}
		}

		if ( levels[i].size() == 0 )
			break;
	}
}
