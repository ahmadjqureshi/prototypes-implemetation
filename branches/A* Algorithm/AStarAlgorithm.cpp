// AStarAlgorithm.cpp : Defines the entry point for the console application.
//
#ifdef WIN32
#include "stdafx.h"
#endif

#include "shortestpathimpl.h"

Graph contructGraphFromFile()
{
	Graph	g1;
	int		i;

	int numberOfEdges, start, end, weight, numberOfVertex, vertexNumber, heuristicValue;
	FILE *file;

	file = fopen( "hurestics.txt", "r" );

	if ( file == NULL)
	{
		printf("No hurestics.txt found in present directory. \n");
		return g1;
	}

	fscanf( file, "%d", &numberOfVertex );

	for ( i = 0 ; i < numberOfVertex ; i++ )
	{
		fscanf( file, "%d %d", &vertexNumber, &heuristicValue);
		g1.addHeuristic( vertexNumber, heuristicValue );
	}

	fclose( file );

	file = fopen( "graph.txt", "r");

	if ( file == NULL)
	{
		printf("No graph.txt found in present directory. \n");
		return g1;
	}

	fscanf( file, "%d", &numberOfEdges);

	for ( i = 0 ; i < numberOfEdges ; i++ )
	{
		fscanf( file, "%d %d %d", &start, &end, &weight);
		
		Vertex startV( start, 0, g1.getHeuristic( start ) );
		Vertex endV( end, 0, g1.getHeuristic( end) );

		Edge edge( startV, endV, weight);
		g1.insert( edge);
	}

	fclose( file);
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

	Vertex target( intTarget, 0, graph.getHeuristic( intTarget ) );

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

