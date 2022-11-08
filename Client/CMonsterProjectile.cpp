#include "pch.h"
#include "CMonsterProjectile.h"

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

	pEffect->GetAnimator()->LoadAnimation(L"animation\\Effect\\BURN_EFFECT_2.anim");
	pEffect->GetAnimator()->Play(false);
	
	Instantiate(pEffect, GetPos(), ELAYER::EFFECT);
	SetDead();
}

void CMonsterProjectile::OnOverlap(CCollider* _pOther)
{
}

void CMonsterProjectile::EndOverlap(CCollider* _pOther)
{
}
