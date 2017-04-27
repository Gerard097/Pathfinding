#include "Graph.h"
#include <algorithm>

CGraph::CGraph() :
	m_iRows{ 0 },
	m_iCols{ 0 },
	m_pBegin{ nullptr },
	m_pEnd{ nullptr },
	m_pConnections{ nullptr }
{
}

CGraph::CGraph( const CGraph & graph )
{
	*this = graph;
}

CGraph& CGraph::operator=( const CGraph & graph )
{
	m_iRows = graph.m_iRows;
	m_iCols = graph.m_iRows;

	m_nodes.reserve( graph.m_nodes.size() );

	for ( auto& pNode : graph.m_nodes )
	{
		auto pNewNode = std::make_unique<CGraphNode>( *pNode );
		pNewNode->SetGraph( this );
		m_nodes.push_back( std::move(pNewNode) );
	}

	m_heuristicFunc = graph.m_heuristicFunc;

	if ( graph.m_pBegin )
		SetBegin( graph.m_pBegin->GetID() );
	else
		m_pBegin = nullptr;

	if ( graph.m_pEnd )
		SetBegin( graph.m_pEnd->GetID() );
	else
		m_pEnd = nullptr;

	m_pConnections = &const_cast<CGraph&>(graph).m_connections;

	return *this;
}

CGraph::~CGraph()
{
}

CGraphNode* CGraph::GetNode( id_type id )
{
	return ((int)id >= 0 && (int)id < (m_iRows * m_iCols)) ? m_nodes[id].get() : nullptr;
}

CGraphNode* CGraph::GetBeginNode()
{
	return m_pBegin;
}

CGraphNode* CGraph::GetEndNode()
{
	return m_pEnd;
}

CGraph::ConnectionsMap CGraph::GetConnections()
{
	return m_pConnections ? *m_pConnections : m_connections;
}

std::vector<CGraphNode*> CGraph::GetNodeConnections( CGraphNode * pNode )
{
	auto nodeConnections = m_pConnections ? m_pConnections->find(pNode->GetID()) : m_connections.find( pNode->GetID() );

	std::vector<CGraphNode*> connections;

	auto connEnd = m_pConnections ? m_pConnections->end() : m_connections.end();

	if ( nodeConnections != connEnd )
	{
		for ( auto& connection_id : nodeConnections->second )
		{
			connections.emplace_back( GetNode( connection_id ) );
		}
	}

	return std::move( connections );
}

std::vector<CGraphNode*> CGraph::GetNodes()
{
	std::vector<CGraphNode*> out;

	out.reserve( m_nodes.size() );
	
	for ( auto& pNode : m_nodes )
		out.emplace_back( pNode.get() );

	return std::move( out );
}

void CGraph::Create( int iCols, int iRows, float fNodeWidth, float fNodeHeight, Connections::Type connType )
{
	Clean();

	m_iRows = iRows;
	m_iCols = iCols;

	m_nodes.reserve( iCols * iRows );

	for ( int i = 0; i < (iCols * iRows); ++i )
	{
		auto pNode = std::make_unique<CGraphNode>( i, this );
		pNode->SetPosition( { i % iCols * fNodeWidth,
								i / iCols * fNodeHeight, 0.f, 1.f } );
		m_nodes.push_back( std::move( pNode ) );
	}

	for ( int i = 0; i < (iCols * iRows); ++i )
	{
		const int x = i % iCols;
		const int y = i / iCols;

		const int iLeft = std::max( x - 1, 0 );
		const int iRight = std::min( x + 1, iCols - 1 );
		const int iTop = std::max( y - 1, 0 );
		const int iDown = std::min( y + 1, iRows - 1 );

		AddConnection( iLeft + y * iCols, i, true );
		AddConnection( iRight + y * iCols, i, true );
		AddConnection( iTop * iCols + x, i, true );
		AddConnection( iDown * iCols + x, i, true );

		if ( connType == Connections::EIGHT_DIRECTIONS )
		{
			AddConnection( iLeft + iTop * iCols, i, true );
			AddConnection( iRight + iDown * iCols, i, true );
			AddConnection( iTop * iCols + iRight, i, true );
			AddConnection( iDown * iCols + iLeft, i, true );
		}
	}
}

void CGraph::SetHeuristicFunction( HeuristeicFuncType func )
{
	m_heuristicFunc = func;
}

void CGraph::SetBegin( id_type id )
{
	m_pBegin = GetNode( id );
}

void CGraph::SetEnd( id_type id )
{
	m_pEnd = GetNode( id );
}

void CGraph::Clean()
{
	m_iRows = 0;
	m_iCols = 0;
	m_nodes.clear();
	m_connections.clear();
	m_pConnections = nullptr;
	m_pBegin = nullptr;
	m_pEnd = nullptr;
}

float CGraph::GetNodeHeuristic( CGraphNode* node )
{
	return m_heuristicFunc( node, this );
}

void CGraph::AddConnection( id_type id_from, id_type id_to, bool bBidirectional )
{
	auto pFrom = GetNode( id_from );
	auto pTo = GetNode( id_to );

	if ( pFrom && pTo && pFrom != pTo )
	{
		m_connections[id_from].insert( id_to );
		if ( bBidirectional )
			m_connections[id_to].insert( id_from );
	}
}
