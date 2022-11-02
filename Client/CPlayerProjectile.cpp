#include "pch.h"
#include "CPlayerProjectile.h"

#include "CCollider.h"

#include "CMonster.h"

CPlayerProjectile::CPlayerProjectile()
{
}

CPlayerProjectile::~CPlayerProjectile()
{
}

void CPlayerProjectile::BeginOverlap(CCollider* _pOther)
{
	CObj* pObj = _pOther->GetOwner();

	if (ELAYER::MONSTER_PROJECTILE == pObj->GetLayer())
	{
		pObj->SetDead();
	}
	else if (ELAYER::MONSTER == pObj->GetLayer())
	{
		CMonster* pMonster = (CMonster*)pObj;

		pMonster->TakeDamage(GetDamage());
	}
}

void CPlayerProjectile::OnOverlap(CCollider* _pOther)
{
}

void CPlayerProjectile::EndOverlap(CCollider* _pOther)
{
}
