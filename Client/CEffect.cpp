#include "pch.h"
#include "CEffect.h"

#include "CAnimator.h"
#include "CAnimation.h"

CEffect::CEffect()
{
	CreateAnimator();
}

CEffect::~CEffect()
{
}

void CEffect::Tick()
{
	if (GetAnimator()->GetCurAnimation()->IsFinish())
	{
		SetDead();
	}

	CObj::Tick();
}
