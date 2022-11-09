#include "pch.h"
#include "CGaibonSkyAttack.h"

#include "CTimeMgr.h"
#include "CRigidBody.h"

#include "CGaibon.h"

CGaibonSkyAttack::CGaibonSkyAttack()	:
	m_fSkyAttackTime(0.f),
	m_faccAttackTime(0.f)
{
}

CGaibonSkyAttack::~CGaibonSkyAttack()
{
}

void CGaibonSkyAttack::Final_Tick()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	// ³«ÇÏ
	if (m_fSkyAttackTime <= m_faccAttackTime)
	{
		pGaibon->GetRigidBody()->SetGravity(true);
	}
	else
	{
		Vec2 vMonPos = pGaibon->GetPos();

		vMonPos.y -= 100.f * DELTATIME;
		m_faccAttackTime += DELTATIME;
		pGaibon->SetPos(vMonPos);
	}

	if (pGaibon->GetRigidBody()->IsGround())
	{
		ChangeState(L"GaibonMove");
		return;
	}
}

void CGaibonSkyAttack::Enter()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	pGaibon->SkyAttack();

	LARGE_INTEGER llCount;
	QueryPerformanceCounter(&llCount);
	srand((UINT)llCount.QuadPart);
	int a = rand();

	m_fSkyAttackTime = (float)(rand() % 5 + 2);
}

void CGaibonSkyAttack::Exit()
{
	m_fSkyAttackTime = 0.f;
	m_faccAttackTime = 0.f;
}
