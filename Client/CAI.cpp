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
}

void CAI::Tick()
{
}

void CAI::Final_Tick()
{
	m_pCurState->Final_Tick();
}

void CAI::Render(HDC _DC)
{
}

CState* CAI::FindState(const wstring& _strKey)
{
	return nullptr;
}
