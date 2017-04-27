#include "BFSWalker.h"
#include "Graph.h"

CBFSWalker::CBFSWalker() 
{
}

CBFSWalker::~CBFSWalker()
{
}

bool CBFSWalker::Step(  )
{
	if ( m_pEnd && m_pCurrent &&
		 m_iCurrentSteps++ < m_iMaxSteps && !m_nodes.empty() )
	{
		m_pCurrent = m_nodes.front();

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

void CBFSWalker::LoadConnections( CGraphNode *pNode )
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

void CBFSWalker::ClearNodes()
{
	while ( !m_nodes.empty() )
		m_nodes.pop();
}


