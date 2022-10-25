#include "pch.h"
#include "CTrigger.h"

CTrigger::CTrigger()	:
	m_eLevelType(ELEVEL_TYPE::END)
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

void CTrigger::BeginOverlap(CCollider* _pOther)
{
}

void CTrigger::OnOverlap(CCollider* _pOther)
{
}

void CTrigger::EndOverlap(CCollider* _pOther)
{
}

void CTrigger::Save(FILE* _pFile)
{
}

void CTrigger::Load(FILE* _pFile)
{
}
