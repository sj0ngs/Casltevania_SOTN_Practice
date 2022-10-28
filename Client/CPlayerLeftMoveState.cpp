#include "pch.h"
#include "CPlayerLeftMoveState.h"

#include "CPlayer.h"

CPlayerMoveLeftState::CPlayerMoveLeftState()	:
	m_fAccWalkTime(0.f)
{
}

CPlayerMoveLeftState::~CPlayerMoveLeftState()
{
}

void CPlayerMoveLeftState::Final_Tick()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerObj());
	assert(pPlayer);

	if (IS_TAP(EKEY::RIGHT))
	{
		ChangeState(L"Move_Right");
		return;
	}
	else if (IS_PRESSED(EKEY::LEFT))
	{
		if (0.9f <= m_fAccWalkTime)
		{
			pPlayer->GetAnimator()->Play(L"Walk_Left", true);
		}
		Vec2 vPos = pPlayer->GetPos();
		Vec2 vDir = pPlayer->GetDir();
		float fSpeed = pPlayer->GetSpeed();

		vPos -= vDir * fSpeed * DELTATIME;

		pPlayer->SetPos(vPos);

		m_fAccWalkTime += DELTATIME;
	}
	else
	{
		ChangeState(L"Idle");
	}
}

void CPlayerMoveLeftState::Enter()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerObj());
	assert(pPlayer);

	if (pPlayer->IsFaceDirChange())
	{
		//pPlayer->GetAnimator()->Play(L"Turn_Left", false);
	}
	else
	{
		pPlayer->GetAnimator()->Play(L"Walk_Start_Left", false);
	}

	pPlayer->SetFaceDir(false);
}

void CPlayerMoveLeftState::Exit()
{
	m_fAccWalkTime = 0.f;
}