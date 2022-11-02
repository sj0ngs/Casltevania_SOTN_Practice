#include "pch.h"
#include "CAttack.h"

CAttack::CAttack(CObj* _pOwner)
{
	CreateCollider();
}

CAttack::~CAttack()
{
}

void CAttack::Render(HDC _DC)
{
	CObj::Render(_DC);
}

void CAttack::BeginOverlap(CCollider* _pOther)
{
	CPlayerProjectile::BeginOverlap(_pOther);
}

void CAttack::OnOverlap(CCollider* _pOther)
{
}

void CAttack::EndOverlap(CCollider* _pOther)
{
}
