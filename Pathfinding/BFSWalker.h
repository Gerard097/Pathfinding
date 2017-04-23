#ifndef _CBFSWALKER_H_
#define _CBFSWALKER_H_

#include "Walker.h"
#include <queue>


class CBFSWalker : public CWalker
{
public:
	CBFSWalker();
	virtual ~CBFSWalker();
	bool Step() override;
private:
	void LoadConnections( CGraphNode* pNode ) override;
	void ClearNodes() override;
private:
	std::queue<CGraphNode*> m_nodes;
};

#endif //_CBFSWALKER_H_

