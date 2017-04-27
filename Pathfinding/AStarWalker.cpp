#include "AStarWalker.h"
#include "Graph.h"

CAStarWalker::CAStarWalker() 
{
}

CAStarWalker::~CAStarWalker()
{

}

bool CAStarWalker::Step()
{
	if ( m_pEnd && m_pCurrent &&
		 m_iCurrentSteps++ < m_iMaxSteps && !m_nodes.empty() )
	{
		m_pCurrent = *m_nodes.begin();

		m_pCurrent->SetVisited( true );

		m_nodes.erase( m_nodes.begin() );

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


void CAStarWalker::LoadConnections( CGraphNode *pNode )
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

void CAStarWalker::ClearNodes()
{
	m_nodes.clear();
}

/*************Calculador de F**************/

bool CLessF::operator()( CGraphNode *pA, CGraphNode *pB ) const
{
	CGraph* pGraph = pA->GetGraph();
	float hA = pGraph->GetNodeHeuristic( pA );
	float hB = pGraph->GetNodeHeuristic( pB );
	return (hA + pA->GetTentativeDistance()) < (hB + pB->GetTentativeDistance());
}
