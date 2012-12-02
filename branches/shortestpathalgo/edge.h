/*
Edge implementation
*/

#ifndef EDGE_H_
#define EDGE_H_

#include "vertex.h"

class Edge
{
public:
	Edge( int start, int end, int cost)
	{
		m_start.setId( start );
		m_end.setId( end );
		m_cost = cost;
	}

	int		getStart() { return m_start.getId(); }
	Vertex	getVStart() { return m_start; }

	int		getEnd() { return m_end.getId(); }
	Vertex	getVEnd() { return m_end; }

	int		getCost() { return m_cost; }


private:
	Vertex			m_start;
	Vertex			m_end;
	unsigned int	m_cost;
};

#endif
