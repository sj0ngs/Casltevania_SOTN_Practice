#include "pch.h"
#include "CAI.h"

#include "CState.h"

AI::AI(CObj* _pOwner)	:
	CComponent(_pOwner),
	m_pCurState(nullptr)
{
}

AI::AI(const AI& _Other)	:
	CComponent(nullptr),
	m_pCurState(nullptr)
{
	map<wstring, CState*>::const_iterator iter = _Other.m_mapState.begin();

	for (; iter != _Other.m_mapState.end(); ++iter)
	{
	    CState* pState = iter->second->Clone();
		pState->m_pOwnerAI = this;
		m_mapState.insert(make_pair(iter->first, pState));

		if (iter->second == _Other.m_pCurState)
			m_pCurState = pState;
	}
}

AI::~AI()
{
	map<wstring, CState*>::iterator iter = m_mapState.begin();

	for (; iter != m_mapState.end(); ++iter)
	{
		DYNAMIC_DELETE(iter->second);
	}
	m_mapState.clear();
}

void AI::Final_Tick()
{
	if (nullptr == m_pCurState)
		return;

	m_pCurState->Final_Tick();
}

void AI::AddState(const wstring& _strKey, CState* _pState)
{
	_pState->m_pOwnerAI = this;
	m_mapState.insert(make_pair(_strKey, _pState));
}

CState* AI::FindState(const wstring& _strKey)
{
	map<wstring, CState*>::iterator iter = m_mapState.find(_strKey);

	if (iter != m_mapState.end())
		return iter->second;

	return nullptr;
}

void AI::ChangeState(const wstring& _strKey)
{
	CState* pNextState = FindState(_strKey);
	assert(pNextState);

	if (nullptr != m_pCurState)
		m_pCurState->Exit();

	m_pCurState = pNextState;

	pNextState->Enter();
}