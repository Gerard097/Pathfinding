#ifndef _CDFSWALKER_H_
#define _CDFSWALKER_H_

#include "Walker.h"
#include <stack>

class CDFSWalker : public CWalker
{
public:
	CDFSWalker();
	virtual ~CDFSWalker();
	bool Step() override;
private:
	void LoadConnections( CGraphNode* pNode ) override;
	void ClearNodes() override;
private:
	std::stack<CGraphNode*> m_nodes;
};

#endif //_CDFSWALKER_H_
