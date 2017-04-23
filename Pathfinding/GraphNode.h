#ifndef _CGRAPHNODE_H_
#define	_CGRAPHNODE_H_

#include <vector>
#include <AlgebraLib.h>

namespace NodeType
{
	enum T
	{
		BEGIN,
		NORMAL,
		END
	};
}

class CGraph;

class CGraphNode
{
public:
	using id_type = unsigned int;
	CGraphNode( id_type id, CGraph* pGraph, NodeType::T type = NodeType::NORMAL );
	CGraphNode( const CGraphNode& node ) = default;
	CGraphNode& operator=( const CGraphNode& node ) = default;
	bool Visited();
	void SetParent( CGraphNode* parent );
	void SetVisited( bool visit );
	void SetPosition( const Mat4D::CVector4D& pos );
	void SetType( NodeType::T type );
	void SetName( std::string name );
	void SetGraph( CGraph* graph );
	void SetWeight( float fWeight );
	void SetBlocked( bool bBlocked );
	void SetTentativeDistance( float fTentativeDistance );
	Mat4D::CVector4D GetPosition();
	CGraphNode* GetParent();
	NodeType::T GetType();
	id_type     GetID();
	std::string GetName();
	CGraph*     GetGraph();
	float       GetWeight();
	float       GetTentativeDistance();
	bool        IsBlocked();
	~CGraphNode();
private:
	CGraph* m_pGraph;
	std::string m_name;
	NodeType::T m_type;
	CGraphNode*	m_pParent;
	id_type		m_dwID;
	Mat4D::CVector4D m_position;
	bool		m_bVisited;
	bool        m_bBlocked;
	float       m_fWeight;
	float       m_fTentativeDistance;
};

#endif //_CGRAPHNODE_H_

