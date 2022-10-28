#include "pch.h"
#include "CPlayerRightMoveState.h"

#include "CPlayer.h"

CPlayerRightMoveState::CPlayerRightMoveState() :
	m_fAccWalkTime(0.f)
{
}

CPlayerRightMoveState::~CPlayerRightMoveState()
{
}

void CPlayerRightMoveState::Final_Tick()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerObj());
	assert(pPlayer);

	if (IS_TAP(EKEY::LEFT))
	{
		ChangeState(L"Move_Left");
		return;
	}
	else if (IS_PRESSED(EKEY::RIGHT))
	{
		if (0.9 <= m_fAccWalkTime)
		{
			pPlayer->GetAnimator()->Play(L"Walk_Right", true);
		}
		Vec2 vPos = pPlayer->GetPos();
		Vec2 vDir = pPlayer->GetDir();
		float fSpeed = pPlayer->GetSpeed();

		vPos += vDir * fSpeed * DELTATIME;

		pPlayer->SetPos(vPos);
		m_fAccWalkTime += DELTATIME;
	}
	else
	{
		ChangeState(L"Idle");
	}
}

void CPlayerRightMoveState::Enter()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerObj());
	assert(pPlayer);

	if (pPlayer->IsFaceDirChange())
	{
		//pPlayer->GetAnimator()->Play(L"Turn_Left", false);
	}
	else
	{
		pPlayer->GetAnimator()->Play(L"Walk_Start_Right", false);
	}
	pPlayer->SetFaceDir(true);
}

void CPlayerRightMoveState::Exit()
{
	m_fAccWalkTime = 0.f;
}