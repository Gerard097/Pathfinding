#include "GraphNode.h"
#include <algorithm>

CGraphNode::CGraphNode( id_type id, CGraph* pGraph )
	:
	m_pParent{ nullptr },
	m_bVisited{ false },
	m_dwID{ id },
	m_pGraph{ pGraph },
	m_fWeight{ 0 },
	m_bBlocked{ false },
	m_fTentativeDistance{ std::numeric_limits<float>::max() }
{
}

void CGraphNode::SetParent( CGraphNode * parent )
{
	m_pParent = parent;
}

CGraphNode* CGraphNode::GetParent()
{
	return m_pParent;
}

void CGraphNode::SetPosition( const Mat4D::CVector4D & pos )
{
	m_position = pos;
}

Mat4D::CVector4D CGraphNode::GetPosition()
{
	return m_position;
}

void CGraphNode::SetVisited( bool visit )
{
	m_bVisited = visit;
}

bool CGraphNode::Visited()
{
	return m_bVisited;
}

CGraphNode::id_type CGraphNode::GetID()
{
	return m_dwID;
}

void CGraphNode::SetName( std::string name )
{
	m_name = name;
}

std::string CGraphNode::GetName()
{
	return m_name;
}

CGraph *CGraphNode::GetGraph()
{
	return m_pGraph;
}

float CGraphNode::GetWeight()
{
	return m_fWeight;
}

float CGraphNode::GetTentativeDistance()
{
	return m_fTentativeDistance;
}

bool CGraphNode::IsBlocked()
{
	return m_bBlocked;
}

void CGraphNode::SetGraph( CGraph *graph )
{
	m_pGraph = graph;
}

void CGraphNode::SetWeight( float fWeight )
{
	m_fWeight = fWeight;
}

void CGraphNode::SetBlocked( bool bBlocked )
{
	m_bBlocked = bBlocked;
}

void CGraphNode::SetTentativeDistance( float fTentativeDistance )
{
	m_fTentativeDistance = fTentativeDistance;
}


CGraphNode::~CGraphNode()
{
}
