#include "graph.h"

void Graph::addHeuristic( int id, int heuristicValue)
{
	Heuristic addHeuristic;

	addHeuristic.id = id;
	addHeuristic.heuristicValue = heuristicValue;

	m_hurestics.push_back( addHeuristic );
}

int  Graph::getHeuristic(int id)
{
	for (unsigned int i = 0 ; i < m_hurestics.size() ; i++ )
	{
		if ( m_hurestics[i].id == id )
		{
			return m_hurestics[i].heuristicValue;
		}
	}

	return 0;
}
