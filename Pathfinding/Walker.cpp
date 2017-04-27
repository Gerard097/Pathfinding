#include "Walker.h"
#include "Graph.h"
#include "GraphNode.h"

CWalker::CWalker() :
	m_iMaxSteps{ 10000 },
	m_pCurrent{ nullptr },
	m_iCurrentSteps{ 0 },
	m_pEnd{ nullptr },
	m_iBegin{ static_cast<id_type>(-1) },
	m_iEnd{ static_cast<id_type>(-1) }
{
}

CWalker::~CWalker()
{
}

void CWalker::FindPath( const std::shared_ptr<CGraph>& pGraph )
{
	Setup( pGraph );
	while ( !Step() );
	Cleanup();
}

CGraphNode* CWalker::GetCurrentNode()
{
	return m_pCurrent;
}

std::deque<CGraphNode*> CWalker::GetPath()
{
	return m_path;
}

void CWalker::Setup( const std::shared_ptr<CGraph>& pGraph )
{
	m_pGraph = pGraph;

	m_pGraph->SetBegin( m_iBegin );
	m_pGraph->SetEnd( m_iEnd );

	m_iCurrentSteps = 0;

	m_pCurrent = m_pGraph->GetBeginNode();
	m_pEnd = m_pGraph->GetEndNode();

	if ( m_pCurrent )
	{
		m_pCurrent->SetVisited( true );
		m_pCurrent->SetTentativeDistance( m_pCurrent->GetWeight() );
		LoadConnections( m_pCurrent );
	}

	ClearPath();
}

void CWalker::Cleanup()
{
	ClearNodes();
	m_pGraph = nullptr;
	m_pCurrent = nullptr;
	m_pEnd = nullptr;
}

void CWalker::SetMaxSteps( int iMaxSteps )
{
	m_iMaxSteps = iMaxSteps;
}

void CWalker::SetBegin( id_type iBegin )
{
	m_iBegin = iBegin;
}

void CWalker::SetEnd( id_type iEnd )
{
	m_iEnd = iEnd;
}

void CWalker::ClearPath()
{
	m_path.clear();
}

CWalker::id_type CWalker::GetBegin()
{
	return m_iBegin;
}

CWalker::id_type CWalker::GetEnd()
{
	return m_iEnd;
}

void CWalker::CreatePath( CGraphNode *pEnd )
{
	m_path.clear();

	while ( pEnd )
	{
		m_path.push_front( m_pGraph->GetNode( pEnd->GetID() ) );
		pEnd = pEnd->GetParent();
	}

}


std::vector<CGraphNode*> CWalker::GetConnections( CGraphNode * pNode )
{
	return  m_pGraph->GetNodeConnections( pNode );
}