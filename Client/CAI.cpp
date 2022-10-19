#include "pch.h"
#include "CAI.h"

#include "CState.h"

CAI::CAI(CObj* _pOwner)	:
	CComponent(_pOwner),
	m_pCurState(nullptr)
{
}

CAI::~CAI()
{
	map<wstring, CState*>::iterator iter = m_mapState.begin();

	for (; iter != m_mapState.end(); ++iter)
	{
		DYNAMIC_DELETE(iter->second);
	}
	m_mapState.clear();
}

void CAI::Final_Tick()
{
	if (nullptr == m_pCurState)
		return;

	m_pCurState->Final_Tick();
}

void CAI::AddState(const wstring& _strKey, CState* _pState)
{
	_pState->m_pOwnerAI = this;
	m_mapState.insert(make_pair(_strKey, _pState));
}

CState* CAI::FindState(const wstring& _strKey)
{
	map<wstring, CState*>::iterator iter = m_mapState.find(_strKey);

	if (iter != m_mapState.end())
		return iter->second;

	return nullptr;
}

void CAI::ChangeState(const wstring& _strKey)
{
	CState* pNextState = FindState(_strKey);
	assert(pNextState);

	if (nullptr != m_pCurState)
		m_pCurState->Exit();

	m_pCurState = pNextState;

	pNextState->Enter();
}
