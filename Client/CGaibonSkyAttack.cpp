#include "pch.h"
#include "CGaibonSkyAttack.h"

#include "CTimeMgr.h"
#include "CRigidBody.h"

#include "CGaibon.h"
#include "CSlogra.h"

CGaibonSkyAttack::CGaibonSkyAttack() :
	m_fSkyAttackTime(0.f),
	m_faccAttackTime(0.f),
	m_faccFireTime(0.f),
	m_bAttackEnd(false)
{
}

CGaibonSkyAttack::~CGaibonSkyAttack()
{
}

void CGaibonSkyAttack::Final_Tick()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	// ³«ÇÏ
	if (!m_bAttackEnd && m_fSkyAttackTime <= m_faccAttackTime || !pGaibon->IsFly())
	{
		pGaibon->GetRigidBody()->SetGravity(true);
		pGaibon->Landing();
		pGaibon->GetCollider()->SetScale(Vec2(70.f, 220.f));
		pGaibon->GetCollider()->SetOffsetPos(Vec2(0.f, -110.f));
		m_faccAttackTime = m_faccAttackTime;
		m_bAttackEnd = true;
	}
	else if(m_fSkyAttackTime > m_faccAttackTime)
	{
		Vec2 vMonPos = pGaibon->GetPos();

		vMonPos.y -= 100.f * DELTATIME;
		m_faccAttackTime += DELTATIME;

		if (pGaibon->GetFaceDir())
		{
			vMonPos.x -= 150.f * DELTATIME;
		}
		else
		{
			vMonPos.x += 150.f * DELTATIME;
		}

		pGaibon->SetPos(vMonPos);

		m_faccFireTime += DELTATIME;

		if (0.2f <= m_faccFireTime)
		{
			pGaibon->SkyFire();
			m_faccFireTime = 0.f;
		}
	}

	if (pGaibon->GetRigidBody()->IsGround())
	{
		ChangeState(L"GaibonLandAttack");
		return;
	}

	if (pGaibon->GetSlogra())
	{
		CSlogra* pSlogra = pGaibon->GetSlogra();

		if (pSlogra->IsSlograHit())
		{
			ChangeState(L"GaibonTraceSlogra");
		}
	}

	Dead();


}

void CGaibonSkyAttack::Enter()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	pGaibon->SkyAttack();

	LARGE_INTEGER llCount;
	QueryPerformanceCounter(&llCount);
	srand((UINT)llCount.QuadPart);
	int a = rand();

	m_fSkyAttackTime = (float)(rand() % 2  + 2);

	pGaibon->SetFly(true);
}

void CGaibonSkyAttack::Exit()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	m_fSkyAttackTime = 0.f;
	m_faccAttackTime = 0.f;

	pGaibon->SetFly(false);

	m_bAttackEnd = false;
}
