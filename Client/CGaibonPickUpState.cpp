#include "pch.h"
#include "CGaibonPickUpState.h"

#include "CLevelMgr.h"
#include "CTimeMgr.h"

#include "CLevel.h"

#include "CPlayer.h"
#include "CGaibon.h"
#include "CSlogra.h"

CGaibonPickUpState::CGaibonPickUpState()	:
	m_faccPickUpTime(0.f)
{
}

CGaibonPickUpState::~CGaibonPickUpState()
{
}

void CGaibonPickUpState::Final_Tick()
{
	GET_PLAYER();

	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();
	CSlogra* pSlogra = pGaibon->GetSlogra();

	if (nullptr != pSlogra)
	{
		Vec2 vMonPos = pGaibon->GetPos();
		Vec2 vPlayerPos = pPlayer->GetPos();

		m_faccPickUpTime += DELTATIME;

		if (3.f <= m_faccPickUpTime)
		{
			pSlogra->SetSlograCatch(false);
			ChangeState(L"GaibonMove");
			return;
		}

		if (1.f >= m_faccPickUpTime)
		{
			vMonPos.y -= 100.f * DELTATIME;
		}
		else
		{
			float fDist = vPlayerPos.x - vMonPos.x;

			vMonPos.x += fDist * DELTATIME;
		}

		pGaibon->SetPos(vMonPos);
		vMonPos.y += 110.f;
		pSlogra->SetPos(vMonPos);
	}
	else
	{
		ChangeState(L"GaibonMove");
		return;
	}

	Dead();
}

void CGaibonPickUpState::Enter()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();
	CSlogra* pSlogra = pGaibon->GetSlogra();

	if (nullptr != pSlogra)
	{
		pSlogra->SetSlograCatch(true);
	}
}

void CGaibonPickUpState::Exit()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();
	CSlogra* pSlogra = pGaibon->GetSlogra();

	m_faccPickUpTime = 0.f;
	pSlogra->SetSlograCatch(false);
}
