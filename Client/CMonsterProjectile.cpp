#include "pch.h"
#include "CMonsterProjectile.h"

#include "CResMgr.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CEffect.h"

#include "CAnimator.h"

#include "CSound.h"

CMonsterProjectile::CMonsterProjectile()
{
}

CMonsterProjectile::~CMonsterProjectile()
{
}

void CMonsterProjectile::BeginOverlap(CCollider* _pOther)
{
	CEffect* pEffect = (CEffect*)CObjMgr::GetInst()->FindObj(L"Burn_Effect_3")->Clone();
	
	Instantiate(pEffect, GetPos(), ELAYER::EFFECT);
	SetDead();

	CSound* pSound = CResMgr::GetInst()->FindSound(L"Projectile_Explot");
	pSound->Play();
}

void CMonsterProjectile::OnOverlap(CCollider* _pOther)
{
}

void CMonsterProjectile::EndOverlap(CCollider* _pOther)
{
}
