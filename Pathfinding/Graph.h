#ifndef _CGRAPH_H_
#define _CGRAPH_H_

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#include "GraphNode.h"

class CGraph
{
public:
	using id_type = unsigned int;
	using ConnectionsMap = std::unordered_map<id_type, std::unordered_set<id_type>>;
	using NodesMap = std::unordered_map<id_type, std::unique_ptr<CGraphNode>>;
	CGraph();
	CGraph( const CGraph& graph );
	~CGraph();
	CGraph& operator=( const CGraph& graph );
	CGraphNode* GetNode( id_type id );
	CGraphNode* GetBeginNode();
	CGraphNode* GetEndNode();
	void AddNode( std::unique_ptr<CGraphNode> newNode );
	void CreateNode( id_type id );
	void RemoveNode( id_type id );
	void AddConnection( CGraphNode* pFrom, CGraphNode* pTo, bool bBidirectional );
	void RemoveConnection( CGraphNode *pFrom, CGraphNode *pTo, bool bBidirectional );
	void RemoveNodeConnections( CGraphNode* pNode );
	void RemoveNodeFromConnections( CGraphNode* pNode );
	float GetNodeHeuristic( CGraphNode* node );
	ConnectionsMap GetConnections();
	std::vector<CGraphNode*> GetNodeConnections( CGraphNode* node );
	std::vector<CGraphNode*> GetNodes();
	void SetBegin( id_type id );
	void SetEnd( id_type id );
	void SetHeuristicFunction( std::function<float( CGraphNode* node, CGraph* graph )> func );
	void Clean();
private:
private:
	std::function<float( CGraphNode* node, CGraph* graph )> m_heuristicFunc;
	std::unique_ptr<CGraphNode> m_pBegin;
	std::unique_ptr<CGraphNode> m_pEnd;
	NodesMap		m_nodes;
	ConnectionsMap	m_connections;
};

#endif //_CGRAPH_H_
