#ifndef CASTARWALKER_H
#define CASTARWALKER_H

#include "Walker.h"
#include <set>

class CLessF
{
public:
	bool operator()( CGraphNode* pA, CGraphNode* pB ) const;
};

class CAStarWalker : public CWalker
{
public:
	CAStarWalker();
	virtual ~CAStarWalker();
	bool Step() override;
private:
	void LoadConnections( CGraphNode* pNode ) override;
	void ClearNodes() override;
private:
	std::multiset<CGraphNode*, CLessF> m_nodes;
};

#endif // CASTARWALKER_H

