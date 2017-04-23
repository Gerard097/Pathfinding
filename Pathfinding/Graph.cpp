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

	m_nodes.reserve( graph.m_nodes.size() );

	for ( auto& node : graph.m_nodes )
	{
		m_nodes.push_back( std::make_unique<CGraphNode>( *node ) );
		m_nodes.back()->SetGraph( this );
	}

	m_connections.reserve( graph.m_connections.size() );
	
	for ( const auto& connection : graph.m_connections )
	{
		for ( const auto& connectedNode : connection.second )
		{
			m_connections[GetNode( connection.first->GetID() )].insert( GetNode( connectedNode->GetID() ) );
		}
	}

	m_heuristicFunc = graph.m_heuristicFunc;

	return *this;
}

void CGraph::AddNode( std::unique_ptr<CGraphNode> newNode )
{
	if ( !newNode ) return;

	if ( newNode->GetType() == NodeType::BEGIN )
	{
		if ( GetBeginNode() )
		{
			m_pBegin->SetType( NodeType::NORMAL );
			m_nodes.push_back( std::move( m_pBegin ) );
		}
		m_pBegin = std::move( newNode );
	}

	else if ( newNode->GetType() == NodeType::END )
	{
		if ( GetEndNode() )
		{
			m_pEnd->SetType( NodeType::NORMAL );
			m_nodes.push_back( std::move( m_pEnd ) );
		}
		m_pEnd = std::move( newNode );
	}
	else
		m_nodes.push_back( std::move( newNode ) );
}

void CGraph::RemoveNode( id_type index )
{
	auto it = m_nodes.begin();
	CGraphNode* pToRemove = nullptr;

	for ( ; it != m_nodes.end(); ++it )
	{
		if ( (*it)->GetID() == index )
			break;
	}

	if ( it != m_nodes.end() )
	{
		pToRemove = it->get();
		m_nodes.erase( it );
	}
	else if ( m_pBegin )
	{
		if ( m_pBegin->GetID() == index )
		{
			pToRemove = m_pBegin.get();
			m_pBegin.reset();
		}

		else if ( m_pEnd )
		{
			if ( m_pEnd->GetID() == index )
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
		m_connections[pFrom].insert( pTo );
		if ( bBidirectional )
			m_connections[pTo].insert( pFrom );
	}
}

void CGraph::RemoveNodeConnections( CGraphNode *pNode )
{
	if ( pNode )
		m_connections.erase( pNode );
}

void CGraph::RemoveNodeFromConnections( CGraphNode *pNode )
{
	for ( auto& connection : m_connections )
	{
		connection.second.erase( pNode );
	}
}

void CGraph::RemoveConnection( CGraphNode *pFrom, CGraphNode *pTo, bool bBidirectional )
{
	if ( pFrom && pTo )
	{
		if ( m_connections.count( pFrom ) )
		{
			m_connections[pFrom].erase( pTo );
		}
		if ( bBidirectional )
		{
			if ( m_connections.count( pTo ) )
			{
				m_connections[pTo].erase( pFrom );
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

CGraphNode* CGraph::GetNode( id_type index )
{
	if ( m_pBegin )
	{
		if ( m_pBegin->GetID() == index )
			return m_pBegin.get();
	}

	if ( m_pEnd )
	{
		if ( m_pEnd->GetID() == index )
			return m_pEnd.get();
	}

	auto lambda = [index]( std::unique_ptr<CGraphNode> const& l )
	{
		return l->GetID() == index;
	};

	auto it = std::find_if( m_nodes.begin(), m_nodes.end(), lambda );

	if ( it != m_nodes.end() )
		return it->get();

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

std::vector<std::unique_ptr<CGraphNode>>::iterator CGraph::GetNodeIt( CGraph::id_type id )
{
	return std::find_if(	m_nodes.begin(), 
							m_nodes.end(), 
							[id]( std::unique_ptr<CGraphNode>& pNode )
							{
								return pNode->GetID() == id;
							}						
						);
}

std::unordered_set<CGraphNode*> CGraph::GetNodeConnections( CGraphNode * node )
{
	return m_connections.count( node ) ? m_connections[node] : std::move( std::unordered_set<CGraphNode*>() );
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
		nodes.emplace_back( node.get() );

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
		m_pBegin->SetType( NodeType::NORMAL );
		m_nodes.push_back( std::move( m_pBegin ) );
	}

	if ( m_pEnd )
		if ( m_pEnd->GetID() == id )
			m_pBegin = std::move( m_pEnd );

	auto it = GetNodeIt( id );

	if ( it != m_nodes.end() )
	{
		m_pBegin = std::move( *it );
		m_nodes.erase( it );
	}

	if ( m_pBegin )
		m_pBegin->SetType( NodeType::BEGIN );

}

void CGraph::SetEnd( CGraph::id_type id )
{
	if ( m_pEnd )
	{
		if ( m_pEnd->GetID() == id )
			return;
		m_pEnd->SetType( NodeType::NORMAL );
		m_nodes.push_back( std::move( m_pEnd ) );
	}

	if ( m_pBegin )
		if ( m_pBegin->GetID() == id )
			m_pEnd = std::move( m_pBegin );

	auto it = GetNodeIt( id );

	if ( it != m_nodes.end() )
	{
		m_pEnd = std::move( *it );
		m_nodes.erase( it );
	}

	if ( m_pEnd )
		m_pEnd->SetType( NodeType::END );
}
