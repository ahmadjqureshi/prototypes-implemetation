#include "paths.h"
#include <algorithm>

using namespace std;

void Paths::findBestPaths( Player turn, Children* levels, int numberOfLevels, bool onlyBestPath, vector<vector<Node>> *paths)
{
	vector<Node*> interestingNodes;
	int i = 0 , j = 0 ;
	bool breakLoop = false;

	if ( numberOfLevels > 4 )
	{
		i = numberOfLevels - 4 ;
	}

	for ( ; i < numberOfLevels ; i+=2 )
	{
		for ( j = 0 ; j < levels[i].size() ; j++ )
		{
			if ( ( turn == Player1 ) && levels[i][j].getBoard().getPlayer1Heuristics() <= 2 )
			{
				interestingNodes.push_back( &levels[i][j]);
			}
			else if ( ( turn == Player2 ) && levels[i][j].getBoard().getPlayer2Heuristics() <= 2 )
			{
				interestingNodes.push_back( &levels[i][j]);
			}
		}
		
	}

	if ( turn == Player1 )
	{
		sort( interestingNodes.begin(), interestingNodes.end(), Paths::myfunction1 );
	}
	else if ( turn == Player2 )
	{
		sort( interestingNodes.begin(), interestingNodes.end(), Paths::myfunction2 );
	}

	for (i = 0 ; i < interestingNodes.size() ; i++ )
	{
		vector<Node> currentPath;
		Node parent = *interestingNodes[i];
		
		while (true)
		{
			currentPath.insert( currentPath.begin(), parent );
			if ( parent.getParent() == NULL)
				break;
			parent = *parent.getParent();
		}

		paths->push_back( currentPath);

		if ( onlyBestPath)
			break;
	}

	
}
