#include "Graph.h"
#include "GraphNode.h"
#include <algorithm>

CGraph::CGraph()
{
}

CGraph::CGraph( const CGraph &graph )
{
	*this = graph;
}

CGraph::~CGraph()
{
}

CGraph &CGraph::operator=( const CGraph &graph )
{
	if ( graph.m_pBegin )
		m_pBegin = std::make_unique<CGraphNode>( *graph.m_pBegin );

	if ( graph.m_pEnd )
		m_pEnd = std::make_unique<CGraphNode>( *graph.m_pEnd );

	for ( auto& node : graph.m_nodes )
	{
		auto pNode = std::make_unique<CGraphNode>( *node.second );
		pNode->SetGraph( this );
		m_nodes.emplace(node.first, std::move(pNode) );
	}

	m_connections = graph.m_connections;

	m_heuristicFunc = graph.m_heuristicFunc;

	return *this;
}

void CGraph::AddNode( std::unique_ptr<CGraphNode> pNewNode )
{
	if ( !pNewNode ) return;

	if ( m_nodes.find( pNewNode->GetID() ) == m_nodes.end() )
	{
		m_nodes[pNewNode->GetID()] = std::move( pNewNode );
	}
}

void CGraph::CreateNode( id_type id )
{
	if ( m_nodes.find( id ) == m_nodes.end() )
	{
		m_nodes[id] = std::make_unique<CGraphNode>( id, this );
	}
}

void CGraph::RemoveNode( id_type id )
{
	auto itNode = m_nodes.find( id );

	CGraphNode* pToRemove = nullptr;

	if ( itNode != m_nodes.end() )
	{
		pToRemove = itNode->second.get();
		m_nodes.erase( itNode );
	}
	else if ( m_pBegin )
	{
		if ( m_pBegin->GetID() == id )
		{
			pToRemove = m_pBegin.get();
			m_pBegin.reset();
		}

		else if ( m_pEnd )
		{
			if ( m_pEnd->GetID() == id )
			{
				pToRemove = m_pEnd.get();
				m_pEnd.reset();
			}
		}
	}

	if ( pToRemove )
	{
		RemoveNodeConnections( pToRemove );
		RemoveNodeFromConnections( pToRemove );
	}
}

void CGraph::AddConnection( CGraphNode *pFrom, CGraphNode *pTo, bool bBidirectional )
{
	if ( pFrom && pTo && pFrom != pTo )
	{
		m_connections[pFrom->GetID()].insert( pTo->GetID() );
		if ( bBidirectional )
			m_connections[pTo->GetID()].insert( pFrom->GetID() );
	}
}

void CGraph::RemoveNodeConnections( CGraphNode *pNode )
{
	m_connections.erase( pNode->GetID() );
}

void CGraph::RemoveNodeFromConnections( CGraphNode *pNode )
{
	for ( auto& connection : m_connections )
	{
		connection.second.erase( pNode->GetID() );
	}
}

void CGraph::RemoveConnection( CGraphNode *pFrom, CGraphNode *pTo, bool bBidirectional )
{
	if ( pFrom && pTo )
	{
		auto fromConnection = m_connections.find( pFrom->GetID() );
		if ( fromConnection != m_connections.end() )
		{
			fromConnection->second.erase( pTo->GetID() );
		}
		if ( bBidirectional )
		{
			auto toConnection = m_connections.find( pTo->GetID() );
			if ( toConnection != m_connections.end() )
			{
				toConnection->second.erase( pFrom->GetID() );
			}
		}
	}

}

float CGraph::GetNodeHeuristic( CGraphNode *node )
{
	return m_heuristicFunc( node, this );
}

CGraph::ConnectionsMap CGraph::GetConnections()
{
	return m_connections;
}

CGraphNode* CGraph::GetNode( id_type id )
{
	if ( m_pBegin )
	{
		if ( m_pBegin->GetID() == id )
			return m_pBegin.get();
	}

	if ( m_pEnd )
	{
		if ( m_pEnd->GetID() == id )
			return m_pEnd.get();
	}

	auto it = m_nodes.find( id );

	if ( it != m_nodes.end() )
		return it->second.get();

	return nullptr;
}

CGraphNode* CGraph::GetBeginNode()
{
	return m_pBegin.get();
}

CGraphNode* CGraph::GetEndNode()
{
	return m_pEnd.get();
}

std::vector<CGraphNode*> CGraph::GetNodeConnections( CGraphNode * pNode )
{
	auto nodeConnections = m_connections.find( pNode->GetID() );

	std::vector<CGraphNode*> connections;

	if ( nodeConnections != m_connections.end() )
	{
		for ( auto& connection_id : nodeConnections->second )
		{
			connections.emplace_back( GetNode( connection_id ) );
		}
	}

	return std::move( connections );
}


void CGraph::SetHeuristicFunction( std::function<float( CGraphNode *, CGraph * )> func )
{
	m_heuristicFunc = func;
}

void CGraph::Clean()
{
	m_connections.clear();
	m_pBegin.reset();
	m_pEnd.reset();
	m_nodes.clear();
}

std::vector<CGraphNode*> CGraph::GetNodes()
{
	std::vector<CGraphNode*> nodes;

	nodes.reserve( m_nodes.size() + 2 );

	for ( auto& node : m_nodes )
		nodes.emplace_back( node.second.get() );

	if ( m_pBegin )
		nodes.emplace_back( m_pBegin.get() );
	if ( m_pEnd )
		nodes.emplace_back( m_pEnd.get() );

	nodes.shrink_to_fit();

	return std::move( nodes );
}

void CGraph::SetBegin( CGraph::id_type id )
{
	if ( m_pBegin )
	{
		if ( m_pBegin->GetID() == id )
			return;
		m_nodes[m_pBegin->GetID()] =  std::move( m_pBegin );
	}

	if ( m_pEnd )
		if ( m_pEnd->GetID() == id )
			m_pBegin = std::move( m_pEnd );

	auto it = m_nodes.find( id );

	if ( it != m_nodes.end() )
	{
		m_pBegin = std::move( it->second );
		m_nodes.erase( it );
	}

}

void CGraph::SetEnd( CGraph::id_type id )
{
	if ( m_pEnd )
	{
		if ( m_pEnd->GetID() == id )
			return;
		m_nodes[m_pEnd->GetID()] = std::move( m_pEnd );
	}

	if ( m_pBegin )
		if ( m_pBegin->GetID() == id )
			m_pEnd = std::move( m_pBegin );

	auto it = m_nodes.find( id );

	if ( it != m_nodes.end() )
	{
		m_pEnd = std::move( it->second );
		m_nodes.erase( it );
	}
}
