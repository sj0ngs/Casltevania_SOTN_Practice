#include "pch.h"
#include "CGaibonTraceSlograState.h"

#include "CGaibon.h"
#include "CSlogra.h"


CGaibonTraceSlograState::CGaibonTraceSlograState()
{
}

CGaibonTraceSlograState::~CGaibonTraceSlograState()
{
}

void CGaibonTraceSlograState::Final_Tick()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	CSlogra* pSlogra = pGaibon->GetSlogra();

	if (nullptr != pSlogra)
	{
		if (pSlogra->IsSlograHit() && pGaibon->IsFly())
		{
			Vec2 vMonPos = pGaibon->GetPos();
			Vec2 vTargetPos = pSlogra->GetPos();
			vTargetPos.y -= 110.f;

			Vec2 vDist = vTargetPos - vMonPos;;

			if (1.f >= vDist.Length())
			{
				ChangeState(L"GaibonPickUp");
				return;
			}

			vDist.Normalize();

			float fSpeed = pGaibon->GetMonsterInfo().m_fTraceSpeed;

			vMonPos.x += vDist.x * fSpeed * 2.f * DELTATIME;
			vMonPos.y += vDist.y * fSpeed * 2.f * DELTATIME;
			pGaibon->SetPos(vMonPos);
		}
		else
		{
			ChangeState(L"GaibonMove");
			return;
		}
	}
	else
	{
		ChangeState(L"GaibonMove");
		return;
	}

	Dead();
}

void CGaibonTraceSlograState::Enter()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	pGaibon->PickUp();
	//CSlogra* pSlogra = pGaibon->GetSlogra();

	pGaibon->SetFly(true);
}

void CGaibonTraceSlograState::Exit()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	pGaibon->SetFly(false);
}
