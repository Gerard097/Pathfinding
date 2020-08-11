#ifndef _CGRAPHNODE_H_
#define	_CGRAPHNODE_H_

#include <vector>
#include <string>
#include <AlgebraLib.h>

class CGraph;

class CGraphNode
{
public:
	using id_type = unsigned int;
	CGraphNode( id_type id, CGraph* pGraph );
	CGraphNode( const CGraphNode& node ) = default;
	CGraphNode& operator=( const CGraphNode& node ) = default;
	bool Visited();
	void SetParent( CGraphNode* parent );
	void SetVisited( bool visit );
	void SetPosition( const Mat4D::CVector4D& pos );
	void SetName( std::string name );
	void SetGraph( CGraph* graph );
	void SetWeight( float fWeight );
	void SetBlocked( bool bBlocked );
	void SetTentativeDistance( float fTentativeDistance );
	Mat4D::CVector4D GetPosition();
	CGraphNode* GetParent();
	id_type     GetID();
	std::string GetName();
	CGraph*     GetGraph();
	float       GetWeight();
	float       GetTentativeDistance();
	bool        IsBlocked();
	~CGraphNode();
private:
	id_type		m_dwID;
	float       m_fTentativeDistance; 
	float       m_fWeight;
	bool		m_bVisited;
	bool        m_bBlocked;
	CGraph* m_pGraph;
	std::string m_name;
	CGraphNode*	m_pParent;
	Mat4D::CVector4D m_position;
};

#endif //_CGRAPHNODE_H_

