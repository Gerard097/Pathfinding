#ifndef _CWALKER_H_
#define _CWALKER_H_

#include <deque>
#include <memory>
#include <vector>

class CGraph;
class CGraphNode;

class CWalker
{
public:
	using id_type = unsigned int;
	CWalker();
	virtual ~CWalker();
	//Find the path in 1 call
	virtual void FindPath( const std::shared_ptr<CGraph>& pGraph );
	//Find the path by steps
	/**********************/
	virtual void Setup( const std::shared_ptr<CGraph>& pGraph );
	virtual bool Step() = 0;
	virtual void Cleanup();
	/**********************/
	//Max number of iterations before cancelling the search
	void SetMaxSteps( int iMaxSteps );
	void SetBegin( id_type iBegin );
	void SetEnd( id_type iEnd );
	void ClearPath();
	id_type GetBegin();
	id_type GetEnd();
	//Used externally when finding the path by steps
	CGraphNode* GetCurrentNode();
	std::deque<CGraphNode*> GetPath();
protected:
	virtual void LoadConnections( CGraphNode* pNode ) = 0;
	virtual void ClearNodes() = 0;
	void CreatePath( CGraphNode* pEnd );
	std::vector<CGraphNode*> GetConnections( CGraphNode* pNode );
protected:
	std::shared_ptr<CGraph> m_pGraph;
	CGraphNode* m_pCurrent;
	CGraphNode* m_pEnd;
	int     m_iMaxSteps;
	int     m_iCurrentSteps;
	id_type m_iBegin;
	id_type m_iEnd;
private:
	std::deque<CGraphNode*> m_path;

};

#endif //_CWALKER_H_
