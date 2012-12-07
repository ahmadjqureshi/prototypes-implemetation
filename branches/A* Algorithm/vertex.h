/*
 * Vertex implementation.
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <stdio.h>

class Vertex
{
public:
	Vertex() : m_parent(NULL)
	{
	}

	Vertex( int id) : m_currentCost(0), m_parent(NULL)
	{
		m_id = id;
	}

	Vertex( int id, int cost) : m_parent(NULL)
	{
		m_id = id;
		m_currentCost = cost;
	}

	Vertex( int id, int cost, int hurestics) : m_parent(NULL)
	{
		m_id = id;
		m_currentCost = cost;
		m_hurestics = hurestics;
	}

	void setId(int id)
	{
		m_id = id;
	}

	void setCost(int cost)
	{
		m_currentCost = cost;
	}

	int getCost() { return m_currentCost ; }

	int getCostWithHurestic() { return m_currentCost + m_hurestics; }

	int getId() { return m_id; }

	void setParent(Vertex *parent)
	{
		m_parent = new Vertex( parent->getId(), parent->getCost() ) ;
	}

	Vertex* getParent() { return m_parent; }

private:
	int m_id;
	int m_currentCost;
	int m_hurestics;
	Vertex* m_parent;
};

#endif
