#include "Graph.h"
#include "BestFSWalker.h"
#include "AStarWalker.h"
#include "DijkstraWalker.h"
#include "BFSWalker.h"
#include "DFSWalker.h"
#include <iostream>
#include <chrono>


auto main( int argc, char** argv ) -> int
{
	auto myGraph = std::make_shared<CGraph>();

	auto manhattanDistance = []( CGraphNode* pNode, CGraph* pGraph )
	{
		auto pEnd = pGraph->GetEndNode();
		float dx = std::fabsf( pNode->GetPosition().x - pEnd->GetPosition().x );
		float dy = std::fabsf( pNode->GetPosition().y - pEnd->GetPosition().y );
		return dx + dy;
	};

	auto euclideanDistance = []( CGraphNode* pNode, CGraph* pGraph )
	{
		auto pEnd = pGraph->GetEndNode();
		return (pEnd->GetPosition() - pNode->GetPosition()).Magnitude();
	};

	const int gridCols = 50;
	const int gridRows = 50;

	myGraph->Create( gridCols, gridRows, 50, 50, Connections::EIGHT_DIRECTIONS );
	myGraph->SetHeuristicFunction( euclideanDistance );

	std::unique_ptr<CWalker> pWalker = std::make_unique<CBestFSWalker>();

	using namespace std::chrono;

	std::cout << "Start\n";

	auto start = steady_clock::now();

	auto pGraphCopy = std::make_shared<CGraph>( *myGraph );

	pWalker->SetBegin( 0 );
	pWalker->SetEnd( gridCols * gridRows - 1 );
	pWalker->FindPath( pGraphCopy );	
	
	auto end = steady_clock::now();

	std::cout << "Time to calculate path: " << duration_cast<duration<float, std::milli>>(end - start).count() << std::endl;

	auto path = pWalker->GetPath();

	if ( path.empty() )
	{
		std::cout << "Couldn't find any path" << std::endl;
	}
	else
	{
		std::cout << "Path found: " << std::endl << std::endl;

		int nNodes = path.size() - 1;

		for ( auto pNode : path )
		{
			std::cout << pNode->GetID();

			if ( nNodes-- )
				std::cout << "->";
		}

	}

	pGraphCopy = nullptr;
	pWalker = nullptr;
	myGraph = nullptr;

	std::cin.ignore( std::numeric_limits<std::streamsize>::max() , '\n' );
	
	return 0;
}
