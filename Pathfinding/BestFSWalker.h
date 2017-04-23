#ifndef BESTFSWALKER_H
#define BESTFSWALKER_H

#include "Walker.h"
#include <queue>
#include <vector>

class CLessHeuristic
{
public:
	bool operator()( CGraphNode* lhs, CGraphNode* rhs ) const;
};

class CBestFSWalker : public CWalker
{
public:
	CBestFSWalker();
	virtual ~CBestFSWalker();
	bool Step( ) override;
private:
	void LoadConnections( CGraphNode* pNode ) override;
	void ClearNodes() override;
private:
	//CLessHeuristic
	std::priority_queue<CGraphNode*,
		std::vector<CGraphNode*>,
		CLessHeuristic> m_nodes;
};


#endif // BESTFSWALKER_H
