#include "decision.h"

#include <vector>
#include <stack>
using namespace std;

void Decision::findBestPaths( Node* rootNode, int numberOfLevels, Board *bestNode)
{
	int i;
	stack<Node*>  open;
	vector<Node*> closed;
	open.push( rootNode );
	rootNode->m_visited = true;

	while ( !open.empty() )
	{
		Node* temp = open.top();
		closed.push_back( temp );

		open.pop();

		for ( i = 0 ; i < temp->getChildrenByRef()->size() ; i++ )
		{

			if ( (*temp->getChildrenByRef())[i]->getChildrenByRef()->size() > 0 && !((*temp->getChildrenByRef())[i]->m_visited))
			{
				(*temp->getChildrenByRef())[i]->m_visited = true;
				open.push( (*temp->getChildrenByRef())[i] );
			}

		}
	}
	
	for ( i = closed.size() - 1 ; i >= 0 ; i-- )
	{
		i = findBestChild( &closed, i);
	}

	*bestNode = (*rootNode->getChildrenByRef())[rootNode->m_indexOfBestChild]->getBoard();

}

int Decision::findBestChild(Node *node)
{
	int i;
	int index = -1;
	int bestHeuristics = 0;

	for ( i = 0 ; i < node->getChildrenByRef()->size() ; i++ )
	{

		if ( (*node->getChildrenByRef())[i]->getTurn() == Player1Turn )
		{
			//Look for lowest Min node
			if ((*node->getChildrenByRef())[i]->getBoard().getPlayer1Heuristics() <= node->m_bestHeuristics )
			{
				node->m_bestHeuristics = (*node->getChildrenByRef())[i]->getBoard().getPlayer1Heuristics();
				index = i;
			}
		}

		if ( (*node->getChildrenByRef())[i]->getTurn() == Player2Turn )
		{
			//Look for highest Max node
			if ((*node->getChildrenByRef())[i]->getBoard().getPlayer2Heuristics() >= node->m_bestHeuristics )
			{
				node->m_bestHeuristics = (*node->getChildrenByRef())[i]->getBoard().getPlayer2Heuristics();
				index = i;
			}
		}

	}

	node->m_indexOfBestChild = index;

	return index;
}
/* The returned int will decide the next node to be examined after alpha or beta pruning.*/
int Decision::findBestChild(vector<Node*> *closed, int closedIndex)
{
	Node* node;
	int i;
	int index = -1;
	int bestHeuristics = 0;

	node = (*closed)[closedIndex];

	for ( i = 0 ; i < node->getChildrenByRef()->size() ; i++ )
	{

		if ( (*node->getChildrenByRef())[i]->getTurn() == Player1Turn )
		{
			//Look for lowest Min node
			if ((*node->getChildrenByRef())[i]->getBoard().getPlayer1Heuristics() <= node->m_bestHeuristics )
			{
				node->m_bestHeuristics = (*node->getChildrenByRef())[i]->getBoard().getPlayer1Heuristics();
				index = i;
			}
		}

		if ( (*node->getChildrenByRef())[i]->getTurn() == Player2Turn )
		{
			//Look for highest Max node
			if ((*node->getChildrenByRef())[i]->getBoard().getPlayer2Heuristics() >= node->m_bestHeuristics )
			{
				node->m_bestHeuristics = (*node->getChildrenByRef())[i]->getBoard().getPlayer2Heuristics();
				index = i;
			}
		}

	}

	node->m_indexOfBestChild = index;

	//try pruning here
	if ( ( closedIndex - 1) > 0 )
	{
		if ( (*closed)[closedIndex]->getParent() != (*closed)[closedIndex - 1] )
		{
			if ( node->getParent()->getTurn() == Player1Turn )
			{
				if ( ((node->getParent()->getBoard().getPlayer1Heuristics()) * -1) >= (*closed)[closedIndex - 1]->getBoard().getPlayer2Heuristics())
				{
					//perform pruning of the sibling or alpha pruning
					closedIndex = closedIndex - 1;
				}
			}

			if ( node->getParent()->getTurn() == Player2Turn )
			{
				if ( ((node->getParent()->getBoard().getPlayer1Heuristics()) * -1) <= (*closed)[closedIndex - 1]->getBoard().getPlayer2Heuristics())
				{
					//perform pruning of the sibling or beta pruning
					closedIndex = closedIndex - 1;
				}
			}
		}
	}

	return closedIndex;
}
