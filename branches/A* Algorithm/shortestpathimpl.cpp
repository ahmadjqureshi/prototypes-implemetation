#include "shortestpathimpl.h"

PathTree ShortestPath::findShortestPath( Graph graph, Vertex start, Vertex target)
{
	PathTree		pathTree;
	vector<Vertex>	open;
	vector<Vertex>  closed;
	vector<Edge>	tempEdges;
	Vertex			tempVertex;
	unsigned int	i , j;
	vector<Vertex>	targetResult;
	bool			foundInClosed, foundInOpen;
	
	open.push_back(start);

	while ( !open.empty() )
	{
		foundInClosed = false;

		tempVertex = open[0];
		open.erase( open.begin() );
		
		if ( target.getId() == tempVertex.getId() )
		{
			targetResult.push_back( tempVertex );

			/*
			Add in the tree to get path
			*/

			pathTree.AddNode( tempVertex );

			return pathTree;
		}

		/*
		check in closed in case we already have lower cost path to this node 
		*/
		foundInClosed = false;
		
		for ( j = 0 ; j < closed.size() ; j++ )
		{
			if ( closed[j].getId() == tempVertex.getId() )
			{
				if ( closed[j].getCost() < tempVertex.getCost() )
				{
					foundInClosed = true;
					/*newVertex = closed[j];
					closed.erase( closed.begin() + j );*/
					break;
				}
			}
		}

		/*
		we do not want to get lost in circular references
		*/
		if ( foundInClosed )
			continue;

		/*get all connections*/
		tempEdges = graph.getConnectedEdges( tempVertex.getId() );
		closed.push_back( tempVertex );
		
		/*
			Add in the tree to get path
		*/
		pathTree.AddNode( tempVertex );

		/*look into all connection and add them into open*/
		for ( i = 0 ; i < tempEdges.size() ; i++ )
		{
			Vertex newVertex = tempEdges[i].getVEnd();
			int costOfNewVertex = tempVertex.getCost() + tempEdges[i].getCost();
			newVertex.setCost( costOfNewVertex);
			newVertex.setParent ( &tempVertex);

			foundInOpen	  = false;

			printf(" From: %d To: %d, costOfNewVertex: %d \n", tempVertex.getId(), newVertex.getId(), costOfNewVertex);
			//Insert in open
			for ( j = 0 ; j < open.size() ; j++ )
			{
				if ( open[j].getCostWithHurestic() > newVertex.getCostWithHurestic() )
				{
					open.insert( open.begin() + j, newVertex);
					foundInOpen = true;
					break;
				}
			}

			if ( !foundInOpen )
			{
				open.push_back( newVertex );
			}
		}
	}

	return pathTree;
}
