/*
This class represents the paths and find paths.
*/

#ifndef _PATHS_H_

#include "node.h"

class Paths
{
public:
	Paths()
	{
	}

	void findBestPaths( Player turn, Children* levels, int numberOfLevels, bool onlyBestPath, vector<vector<Node>> *paths);

private:
	static bool myfunction1 (Node* i,Node* j) { 
													return ( (i->getBoard().getPlayer1Heuristics() < j->getBoard().getPlayer1Heuristics()) ); }
	static bool myfunction2 (Node* i,Node* j) {		
													return ( (i->getBoard().getPlayer2Heuristics() < j->getBoard().getPlayer2Heuristics() ) ); }
};

#endif
