/*
Ahmad Qureshi Initial version

Main program
*/

#ifdef WIN32
#include "stdafx.h"
#endif

#include "shortestpathimpl.h"

Graph contructGraphFromFile()
{
	Graph g1;

	int numberOfEdges, start, end, weight;


	FILE *file = fopen( "graph.txt", "r");

	if ( file == NULL)
	{
		printf("No graph.txt found in present directory. \n");
	}

	fscanf( file, "%d", &numberOfEdges);

	for (int i = 0 ; i < numberOfEdges ; i++ )
	{
		fscanf( file, "%d %d %d", &start, &end, &weight);
		Edge edge( start, end, weight);
		g1.insert( edge);
	}
	return g1;
}


int main(int argc, char* argv[])
{
	printf("----------------------------------\n");
	printf("Trying to load graph from graph.txt \n");
	printf("----------------------------------\n");
	Graph graph = contructGraphFromFile();
	ShortestPath shortestPath;
	int intStart, intTarget;
	
	if ( graph.numberOfEdges() == 0 )
	{
		printf("Unable to load graph.\n");
		return -1;

	}

	printf("\n");
	printf("\nPlease Enter starting node:");

	scanf("%d", &intStart);

	Vertex start( intStart );

	printf("\nPlease Enter target node:");

	scanf("%d", &intTarget);

	Vertex target( intTarget );

	PathTree  pathTree = shortestPath.findShortestPath( graph, start, target);

	vector<vector<Vertex>> pathsFromTree = pathTree.getPaths(start, target);

	for ( unsigned int i = 0 ; i < pathsFromTree.size() ; i++ )
	{
		vector<Vertex> temp = pathsFromTree[i];
		for ( unsigned int j = 0 ; j < temp.size() ; j++ )
		{
			printf( " '%d,%d' ", temp[j].getId(), temp[j].getCost() );
		}
		printf( " \n");
	}

	return 0;
}

