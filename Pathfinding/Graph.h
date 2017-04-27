#ifndef _CGRAPH_H_
#define _CGRAPH_H_

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#include "GraphNode.h"

namespace Connections
{
	enum Type
	{
		EIGHT_DIRECTIONS,
		FOUR_DIRECTIONS
	};
}

class CGraph
{
	friend class GraphCopy;
public:
	using id_type = unsigned int;
	using ConnectionsMap = std::unordered_map<id_type, std::unordered_set<id_type>>;
	using NodesMap = std::vector<std::unique_ptr<CGraphNode>>;
	using HeuristeicFuncType = std::function<float( CGraphNode* node, CGraph* graph )>;
public:
	CGraph();
	CGraph( const CGraph& graph );
	CGraph& operator=( const CGraph& graph );
	~CGraph();
	CGraphNode* GetNode( id_type id );	
	CGraphNode* GetBeginNode();
	CGraphNode* GetEndNode();
	ConnectionsMap GetConnections();
	std::vector<CGraphNode*> GetNodeConnections( CGraphNode* node );
	std::vector<CGraphNode*> GetNodes();
	void Create( int iCols, int iRows, float fNodeWidth, float fNodeHeight, Connections::Type connType );
	void SetHeuristicFunction( HeuristeicFuncType func );
	void SetBegin( id_type id );
	void SetEnd( id_type id );
	void Clean();
	float GetNodeHeuristic( CGraphNode* node );
private:
	void AddConnection( id_type id_from, id_type id_to, bool bBidirectional );
private:
	HeuristeicFuncType m_heuristicFunc;
	int				m_iRows;
	int				m_iCols;
	float			m_fNodeWidth;
	float			m_fNodeHeight;
	NodesMap		m_nodes;
	ConnectionsMap	m_connections;
	ConnectionsMap*	m_pConnections;
	CGraphNode*		m_pBegin;
	CGraphNode*		m_pEnd;
};

#endif //_CGRAPH_H_
