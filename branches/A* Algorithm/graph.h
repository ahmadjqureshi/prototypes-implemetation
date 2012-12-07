/*
Graph implementation
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include "edge.h"
#include <vector>
#include <stdio.h>

using namespace std;

struct heuristic
{
	int id;
	int heuristicValue;
};

typedef heuristic Heuristic;

class Graph
{
public:
	Graph()
	{
	}

	void insert( Edge edge)
	{
		m_edges.push_back(edge );
	}

	vector<Edge> getConnectedEdges(int id)
	{
		vector<Edge> connectedEdges;
		for ( unsigned int i = 0; i < m_edges.size() ; i++ )
		{
			if ( m_edges[i].getStart() == id )
			{
				connectedEdges.push_back( m_edges[i] );
			}
		}

		return connectedEdges;
	}

	unsigned int numberOfEdges()
	{
		return m_edges.size();
	}

	void addHeuristic( int id, int heuristicValue); 

	int  getHeuristic(int id); 

private:
	vector<Edge>		m_edges;
	vector<Heuristic>	m_hurestics;
};

#endif
