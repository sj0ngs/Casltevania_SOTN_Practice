#include "pch.h"
#include "CGaibonLandAttackState.h"

#include "CLevelMgr.h"
#include "CTimeMgr.h"
#include "CRigidBody.h"

#include "CLevel.h"

#include "CGaibon.h"
#include "CPlayer.h"

CGaibonLandAttackState::CGaibonLandAttackState()	:
	m_fLandAttackTime(0.f),
	m_faccAttackTime(0.f),
	m_faccFireTime(0.f)
{
}

CGaibonLandAttackState::~CGaibonLandAttackState()
{
}

void CGaibonLandAttackState::Final_Tick()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	// ³«ÇÏ
	if (m_fLandAttackTime <= m_faccAttackTime)
	{
		ChangeState(L"GaibonMove");
		return;
	}
	else
	{
		m_faccAttackTime += DELTATIME;
		m_faccFireTime += DELTATIME;

		if (1.f <= m_faccAttackTime && 0.2f <= m_faccFireTime)
		{
			pGaibon->LandFire();
			m_faccFireTime = 0.f;
		}
	}

	Dead();
}

void CGaibonLandAttackState::Enter()
{
	GET_PLAYER();

	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	if (EGAIBON_STATE::PHASE_1 == pGaibon->GetGaibonState() &&
		pGaibon->GetMonsterInfo().m_iHP <= pGaibon->GetMonsterInfo().m_iMaxHP / 2.f)
	{
		ChangeState(L"GaibonChange");
	}

	Vec2 vPos = pPlayer->GetPos();
	Vec2 vMonPos = pGaibon->GetPos();
	float fDir = vPos.x - vMonPos.x;

	if (0 <= fDir)
	{
		pGaibon->SetFaceDir(true);
	}
	else
	{
		pGaibon->SetFaceDir(false);
	}

	pGaibon->LandAttack();

	LARGE_INTEGER llCount;
	QueryPerformanceCounter(&llCount);
	srand((UINT)llCount.QuadPart);
	int a = rand();

	m_fLandAttackTime = (float)(rand() % 2 + 2);
}

void CGaibonLandAttackState::Exit()
{
	m_fLandAttackTime = 0.f;
	m_faccAttackTime = 0.f;
}
