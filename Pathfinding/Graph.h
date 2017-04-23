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
	using ConnectionsMap = std::unordered_map<CGraphNode*, std::unordered_set<CGraphNode*>>;
	using id_type = unsigned int;
	CGraph();
	CGraph( const CGraph& graph );
	~CGraph();
	CGraph& operator=( const CGraph& graph );
	CGraphNode* GetNode( id_type id );
	CGraphNode* GetBeginNode();
	CGraphNode* GetEndNode();
	void AddNode( std::unique_ptr<CGraphNode> newNode );
	void RemoveNode( id_type index );
	void AddConnection( CGraphNode* pFrom, CGraphNode* pTo, bool bBidirectional );
	void RemoveConnection( CGraphNode *pFrom, CGraphNode *pTo, bool bBidirectional );
	void RemoveNodeConnections( CGraphNode* pNode );
	void RemoveNodeFromConnections( CGraphNode* pNode );
	float GetNodeHeuristic( CGraphNode* node );
	ConnectionsMap GetConnections();
	std::unordered_set<CGraphNode*> GetNodeConnections( CGraphNode* node );
	std::vector<CGraphNode*> GetNodes();
	void SetBegin( id_type id );
	void SetEnd( id_type id );
	void SetHeuristicFunction( std::function<float( CGraphNode* node, CGraph* graph )> func );
	void Clean();
private:
	std::vector<std::unique_ptr<CGraphNode>>::iterator GetNodeIt( id_type id );
private:
	std::unique_ptr<CGraphNode> m_pBegin;
	std::unique_ptr<CGraphNode> m_pEnd;
	std::vector<std::unique_ptr<CGraphNode>> m_nodes;
	std::function<float( CGraphNode* node, CGraph* graph )> m_heuristicFunc;
	ConnectionsMap m_connections;
};

#endif //_CGRAPH_H_
