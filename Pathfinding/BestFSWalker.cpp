#include "bestfswalker.h"
#include "Graph.h"

CBestFSWalker::CBestFSWalker()
{

}

CBestFSWalker::~CBestFSWalker()
{

}
bool CBestFSWalker::Step( )
{
	if ( m_pEnd && m_pCurrent &&
		 m_iCurrentSteps++ < m_iMaxSteps && !m_nodes.empty() )
	{
		m_pCurrent = m_nodes.top();

		m_pCurrent->SetVisited( true );

		m_nodes.pop();

		if ( m_pCurrent == m_pEnd )
		{
			CreatePath( m_pCurrent );
			return true;
		}

		LoadConnections( m_pCurrent );

	}
	else
	{
		//CreatePath(m_pCurrent);
		return true;
	}

	return false;
}

void CBestFSWalker::LoadConnections( CGraphNode* pNode )
{
	auto connections = std::move( GetConnections( pNode ) );

	for ( auto& node : connections )
	{
		if ( !node->Visited() && !node->GetParent() && !node->IsBlocked() )
		{
			m_nodes.push( node );
			node->SetParent( pNode );
		}
	}
}

void CBestFSWalker::ClearNodes()
{
	while ( m_nodes.size() )
	{
		m_nodes.pop();
	}
}

/*********CLessHeuristic******/
bool CLessHeuristic::operator()( CGraphNode *lhs, CGraphNode *rhs ) const
{
	CGraph* graph = lhs->GetGraph();
	return graph->GetNodeHeuristic( lhs ) > graph->GetNodeHeuristic( rhs );
}
