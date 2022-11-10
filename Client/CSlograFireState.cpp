#include "pch.h"
#include "CSlograFireState.h"

#include "CTimeMgr.h"

#include "CSlogra.h"


CSlograFireState::CSlograFireState()	:
	m_bFireEnd(false),
	m_faccFireTime(0.f)
{
}

CSlograFireState::~CSlograFireState()
{
}

void CSlograFireState::Final_Tick()
{
	CSlogra* pSlogra = (CSlogra*)GetOwnerObj();

	m_faccFireTime += DELTATIME;

	if (!m_bFireEnd && 3 == pSlogra->GetAnimator()->GetCurAnimation()->GetCurFrame())
	{
		pSlogra->Fire();
		m_bFireEnd = true;
	}

	if (1.5f <= m_faccFireTime)
	{
		ChangeState(L"SlograIdle");
	}

	Dead();
}

void CSlograFireState::Enter()
{
	CSlogra* pSlogra = (CSlogra*)GetOwnerObj();

	if (pSlogra->GetFaceDir())
	{
		pSlogra->GetAnimator()->Play(L"Slogra_Spear_Fire_Right", false);
	}
	else
	{
		pSlogra->GetAnimator()->Play(L"Slogra_Spear_Fire_Left", false);
	}

	pSlogra->SlograStartFire();
}

void CSlograFireState::Exit()
{
	m_faccFireTime = 0.f;
	m_bFireEnd =false;
}
