#include "Graph.h"
#include "BestFSWalker.h"
#include "AStarWalker.h"
#include "DijkstraWalker.h"
#include "BFSWalker.h"
#include "DFSWalker.h"
#include <iostream>
#include <chrono>

void CreateGrid( int x, int y, CGraph* pGraph );

auto main( int argc, char** argv ) -> int
{
	CGraph myGraph;

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

	myGraph.SetHeuristicFunction( euclideanDistance );

	std::unique_ptr<CWalker> pWalker = std::make_unique<CAStarWalker>();

	const int gridCols = 150;
	const int gridRows = 150;

	CreateGrid( gridCols, gridRows, &myGraph );

	using namespace std::chrono;

	std::cout << "Start\n";

	auto start = steady_clock::now();

	auto pGraphCopy = std::make_shared<CGraph>( myGraph );

	pWalker->SetBegin( 0 );
	pWalker->SetEnd( gridCols * gridRows - 1 );
	pWalker->FindPath( pGraphCopy );	
	
	auto end = steady_clock::now();

	std::cout << "Time to calculate path: " << duration<float>(end - start).count() << std::endl;

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

	std::cin.ignore( std::numeric_limits<std::streamsize>::max() , '\n' );
	
	return 0;
}

void CreateGrid( int cols, int rows, CGraph * pGraph )
{
	pGraph->Clean();

	std::cout << "Graph:" << std::endl << std::endl;

	for ( int y = 0; y < rows; ++y )
	{
		for ( int x = 0; x < cols; ++x )
		{

			int current = y * rows + x;

			/*if ( x )
				std::cout << "\t";
			std::cout << current ;
			if ( x < (cols - 1) )
				std::cout << "\t-";*/
			pGraph->CreateNode( current );
			auto pCurrent = pGraph->GetNode( current );
			pCurrent->SetPosition( { x * 20.f, y * 20.f, 0.f , 0.f } );
			int left = std::max( 0, x - 1 );
			int top = std::max( 0, y - 1 );
			pGraph->AddConnection( pCurrent, pGraph->GetNode( y * rows + left ), true );
			pGraph->AddConnection( pCurrent, pGraph->GetNode( top * cols + x ), true );
		}

		/*std::cout << std::endl;
		if ( y < (rows - 1) )
		{
			for ( int i = 0; i < cols; ++i )
			{
				if ( i ) std::cout << "\t\t";
				std::cout << "|";
			}
			
			std::cout << std::endl;
		}*/

	}

	//std::cout << std::endl;
}
