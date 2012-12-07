/*
 The path tree is based on stl vector just to keep implementation simple as we are not going to do any deletion from the tree.

 When the tree is constructed for short paths we do a bottom up traversal to create path.
*/

#ifndef PATHTREE_H_
#define PATHTREE_H_

#include "vertex.h"
#include <vector>

using namespace std;

class PathTreeNode
{
public:
	PathTreeNode() : m_parent(0)
	{
	}
	
	//Identity of vertex
	int						m_id;
	//Cost of Vertex
	int						m_cost;
	
	// Indexes that are children of this vertex main Vector m_nodes in PathTree class
	vector<int>				m_children;

	// Parent index 
	int						m_parent;
};

class PathTree
{
public:
	PathTree()
	{
	}

	vector<PathTreeNode> m_nodes;

	bool AddNode( Vertex node);

	vector<vector<Vertex>> getPaths( Vertex start, Vertex target);
	
};

#endif
