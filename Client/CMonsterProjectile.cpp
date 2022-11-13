#include "pch.h"
#include "CMonsterProjectile.h"

#include "CObjMgr.h"
#include "CPlayer.h"
#include "CEffect.h"

#include "CAnimator.h"

CMonsterProjectile::CMonsterProjectile()
{
}

CMonsterProjectile::~CMonsterProjectile()
{
}

void CMonsterProjectile::BeginOverlap(CCollider* _pOther)
{
	CEffect* pEffect = new CEffect;

	pEffect = (CEffect*)CObjMgr::GetInst()->FindObj(L"Burn_Effect_3")->Clone();
	
	Instantiate(pEffect, GetPos(), ELAYER::EFFECT);
	SetDead();
}

void CMonsterProjectile::OnOverlap(CCollider* _pOther)
{
}

void CMonsterProjectile::EndOverlap(CCollider* _pOther)
{
}
