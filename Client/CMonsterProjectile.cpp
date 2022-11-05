#include "pch.h"
#include "CMonsterProjectile.h"

#include "CPlayer.h"

CMonsterProjectile::CMonsterProjectile()
{
}

CMonsterProjectile::~CMonsterProjectile()
{
}

void CMonsterProjectile::BeginOverlap(CCollider* _pOther)
{
	SetDead();
}

void CMonsterProjectile::OnOverlap(CCollider* _pOther)
{
}

void CMonsterProjectile::EndOverlap(CCollider* _pOther)
{
}
