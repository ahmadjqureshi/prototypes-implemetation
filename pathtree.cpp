#include "pathtree.h"

bool PathTree::AddNode( Vertex node)
{
	int parentIndex = -1, myIndex = -1, i;
	PathTreeNode treeNode;
	treeNode.m_id = node.getId();
	treeNode.m_cost = node.getCost();

	if ( ( m_nodes.size() == 0 ) && ( node.getParent() == NULL ) )
	{
		m_nodes.push_back( treeNode );
		return true;
	}

	m_nodes.push_back( treeNode );

	Vertex parentNode = *node.getParent();
	myIndex = m_nodes.size() - 1;

	for ( i = 0 ; i < m_nodes.size() ; i++ )
	{
		if ( ( parentNode.getId() == m_nodes[i].m_id ) && ( parentNode.getCost() == m_nodes[i].m_cost ) )
		{
			parentIndex = i;
			break;
		}
	}

	if ( (parentIndex >= 0 ) && ( myIndex >= 0 ) )
	{
		m_nodes[parentIndex].m_children.push_back( myIndex );
		m_nodes[myIndex].m_parent = parentIndex;
		return true;
	}

	return false;
}

vector<vector<Vertex>> PathTree::getPaths( Vertex start, Vertex target)
{
	vector<vector<Vertex>>	paths;
	vector<int>		targetIndex;
	unsigned int	i,j;

	for ( i = 0 ; i < m_nodes.size() ; i++)
	{
		if ( m_nodes[i].m_id == target.getId() )
			targetIndex.push_back( i );
	}

	for (i = 0 ; i < targetIndex.size() ; i++ )
	{
		vector<Vertex> temppath;
		j = targetIndex[i];
		Vertex temp( m_nodes[j].m_id, m_nodes[j].m_cost);
		temppath.push_back( temp);
			
		while (m_nodes[j].m_id != start.getId() )
		{
			j = m_nodes[j].m_parent;
			Vertex temp1( m_nodes[j].m_id, m_nodes[j].m_cost);
			temppath.insert( temppath.begin(), temp1);
		}

		paths.push_back( temppath );
	}

	return paths;
}
