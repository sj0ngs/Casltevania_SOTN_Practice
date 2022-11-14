#include "pch.h"
#include "CAttack.h"

#include "CEffect.h"
#include "CAnimator.h"

CAttack::CAttack(CObj* _pOwner)
{
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

	CEffect* pEffect = new CEffect;
	pEffect->GetAnimator()->LoadAnimation(L"animation\\Effect\\HIT_EFFECT.anim");
	pEffect->GetAnimator()->Play(L"Hit_Effect", false);

	Instantiate(pEffect, GetCollider()->GetFinalPos(), ELAYER::EFFECT);
}

void CAttack::OnOverlap(CCollider* _pOther)
{
}

void CAttack::EndOverlap(CCollider* _pOther)
{
}
