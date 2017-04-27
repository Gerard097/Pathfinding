#include "DijkstraWalker.h"
#include "Graph.h"

CDijkstraWalker::CDijkstraWalker()
{

}

CDijkstraWalker::~CDijkstraWalker()
{

}

bool CDijkstraWalker::Step()
{
	if ( m_pEnd && m_pCurrent &&
		 m_iCurrentSteps++ < m_iMaxSteps && !m_nodes.empty() )
	{
		m_pCurrent = *m_nodes.begin();
		m_nodes.erase( m_nodes.begin() );

		if ( m_pCurrent != m_pEnd )
		{
			m_pCurrent->SetVisited( true );
			LoadConnections( m_pCurrent );
		}
		else
			CreatePath( m_pCurrent );
	}
	else
	{
		return true;
	}

	return false;
}

void CDijkstraWalker::LoadConnections( CGraphNode *pNode )
{
	auto connections = std::move( GetConnections( pNode ) );

	for ( auto& node : connections )
	{
		float fTentDist = pNode->GetTentativeDistance() + node->GetWeight();
		float fNodeTent = node->GetTentativeDistance();
		if ( !node->Visited() && !node->IsBlocked() &&
			 fTentDist < fNodeTent )
		{
			auto it = m_nodes.find( node );

			if ( it != m_nodes.end() )
			{
				m_nodes.erase( it );
			}

			node->SetTentativeDistance( fTentDist );

			m_nodes.insert( node );

			node->SetParent( pNode );
		}
	}
}

void CDijkstraWalker::ClearNodes()
{
	m_nodes.clear();
}


/*******Clase Para Comprar pesos******/

bool CLessWeight::operator()( CGraphNode *lhs, CGraphNode *rhs ) const
{
	return lhs->GetTentativeDistance() < rhs->GetTentativeDistance();
}
