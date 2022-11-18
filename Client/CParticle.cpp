#include "pch.h"
#include "CParticle.h"

#include "CTimeMgr.h"
#include "CAnimator.h"

#include "CAnimation.h"

CParticle::CParticle()	:
	m_pTarget(nullptr)
{
	CreateAnimator();

	GetAnimator()->LoadAnimation(L"animation\\Effect\\PARTICLE_1.anim");
	GetAnimator()->Play(true);
}

CParticle::~CParticle()
{
}

void CParticle::Tick()
{
	if (IsValid(m_pTarget))
	{
		Vec2 vTargetPos = m_pTarget->GetPos();
		vTargetPos.y -= 140.f;
		Vec2 vPos = GetPos();

		Vec2 vDir = vTargetPos - vPos;
		
		float fDist = vDir.Length();

		if (1.f >= fDist)
		{
			SetDead();
			return;
		}
		else
		{
			vDir.Normalize();

			vPos.x += vDir.x * 500.f * DELTATIME;
			vPos.y += vDir.y * 500.f * DELTATIME;

			SetPos(vPos);
		}
	}

	CObj::Tick();
}

void CParticle::SetFrm(UINT _iFrm)
{
	if (GetAnimator()->GetCurAnimation())
	{
		UINT iFrm = _iFrm % 8;
		GetAnimator()->GetCurAnimation()->SetCurFrame(iFrm);
	}
}
