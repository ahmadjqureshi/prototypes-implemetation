#ifndef SHORTESTPATH_H_
#define SHORTESTPATH_H_

#include <stack>
#include <vector>

#include "graph.h"
#include "pathtree.h"

using namespace std;

class ShortestPath
{
public:
	ShortestPath()
	{
	}

	PathTree findShortestPath( Graph graph, Vertex start, Vertex target);
	
};
#endif
