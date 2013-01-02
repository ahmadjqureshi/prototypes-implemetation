/*The Decision class implements Minimax algo to search game tree and it also performs pruning*/

#ifndef _DECISION_H
#define _DECISION_H

#include "node.h"

class Decision
{
public:
	Decision()
	{
	}

	void findBestPaths( Node* rootNode, int numberOfLevels, Board *bestNode);

private:
	//findBestChild(Node *node) is Not used it was old implementation just kept for any future work.
	int findBestChild(Node *node);

	int findBestChild(vector<Node*> *closed, int index);
};

#endif
