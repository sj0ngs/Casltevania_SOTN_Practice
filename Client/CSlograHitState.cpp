#include "pch.h"
#include "CSlograHitState.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CSlogra.h"
#include "CPlayer.h"

CSlograHitState::CSlograHitState()	:
	m_faccHitTime(0.f)
{
}

CSlograHitState::~CSlograHitState()
{
}

void CSlograHitState::Final_Tick()
{
	CSlogra* pSlogra = (CSlogra*)GetOwnerObj();

	m_faccHitTime += DELTATIME;

	if (pSlogra->IsSlograCatch())
	{
		ChangeState(L"SlograDrop");
		return;
	}

	if (SLOGRA_HIT_TIME <= m_faccHitTime)
	{
		ChangeState(L"SlograIdle");
		return;
	}

	Dead();
}

void CSlograHitState::Enter()
{	
	GET_PLAYER();

	CSlogra* pSlogra = (CSlogra*)GetOwnerObj();
	Vec2 vDir = pPlayer->GetPos() - pSlogra->GetPos();

	if (vDir.x >= 0)
	{
		pSlogra->SetFaceDir(true);
	}
	else
	{
		pSlogra->SetFaceDir(false);
	}

	pSlogra->Hit();
}

void CSlograHitState::Exit()
{
	CSlogra* pSlogra = (CSlogra*)GetOwnerObj();

	m_faccHitTime = 0.f;

	pSlogra->SetSlograHit(false);
}
