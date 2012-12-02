#include "shortestpathimpl.h"

PathTree ShortestPath::findShortestPath( Graph graph, Vertex start, Vertex target)
{
	PathTree		pathTree;
	stack<Vertex>	open;
	vector<Vertex>  closed;
	vector<Edge>	tempEdges;
	Vertex			tempVertex;
	unsigned int	i , j;
	vector<Vertex>	targetResult;
	bool			foundInClosed, lowerCostVertex;
	
	open.push(start);

	while ( !open.empty() )
	{
		foundInClosed = false;

		tempVertex = open.top();
		open.pop();

		/*
		check in closed in case we already have lower cost path to this node
		*/
		
		for ( i = 0 ; i < closed.size() ; i++ )
		{
			if ( closed[i].getId() == tempVertex.getId() )
			{
				if ( closed[i].getCost() <= tempVertex.getCost() )
				{
					foundInClosed = true;
					break;
				}
			}
		}

		if ( foundInClosed )
			continue;

		if ( target.getId() == tempVertex.getId() )
		{
			targetResult.push_back( tempVertex );

			/*
			Add in the tree to get path
			*/

			pathTree.AddNode( tempVertex );

			continue;
		}

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

			//printf(" From: %d To: %d, costOfNewVertex: %d \n", tempVertex.getId(), newVertex.getId(), costOfNewVertex);
			open.push( newVertex);
		}
	}

	return pathTree;
}
