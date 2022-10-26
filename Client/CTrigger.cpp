#include "pch.h"
#include "CTrigger.h"

CTrigger::CTrigger()	:
	m_eType(ETRIGGER_TYPE::NONE)
{
	CreateCollider();
}

CTrigger::~CTrigger()
{
}

void CTrigger::Render(HDC _DC)
{
	CObj::Render(_DC);
}

void CTrigger::Save(FILE* _pFile)
{
}

void CTrigger::Load(FILE* _pFile)
{
}
