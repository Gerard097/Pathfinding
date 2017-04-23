#ifndef CDIJKSTRAWALKER_H
#define CDIJKSTRAWALKER_H

#include "Walker.h"
#include <set>

class CLessWeight
{
public:
	bool operator()( CGraphNode* lhs, CGraphNode* rhs ) const;
};

class CDijkstraWalker : public CWalker
{
public:
	CDijkstraWalker();
	virtual ~CDijkstraWalker();
	bool Step() override;
private:
	void LoadConnections( CGraphNode* pNode ) override;
	void ClearNodes() override;
private:
	std::multiset<CGraphNode*, CLessWeight> m_nodes;
};

#endif // CDIJKSTRAWALKER_H
