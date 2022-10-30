#include "pch.h"
#include "CPlayerRightMoveState.h"

#include "CPlayer.h"

CPlayerRightMoveState::CPlayerRightMoveState()
{
}

CPlayerRightMoveState::~CPlayerRightMoveState()
{
}

void CPlayerRightMoveState::Final_Tick()
{
	GET_PLAYER();

	if (IS_TAP(EKEY::SPACE))
		ChangeState(L"Jump");
	else if (!pPlayer->GetRigidBody()->IsGround())
		ChangeState(L"Fall");
	else if (IS_TAP(EKEY::DOWN))
		ChangeState(L"Duck");
	else if (IS_TAP(EKEY::LSHIFT))
		ChangeState(L"BackDash");

	if (IS_TAP(EKEY::LEFT))
	{
		ChangeState(L"Move_Left");
		return;
	}
	else if (IS_PRESSED(EKEY::RIGHT))
	{
		if (GetAnim()->IsFinish())
		{
			pPlayer->GetAnimator()->Play(L"Walk_Right", true);
		}
	}
	else if(IS_RELEASED(EKEY::RIGHT))
	{
		if (GetAnim()->IsFinish())
			ChangeState(L"MoveEnd");
		else
			ChangeState(L"Idle");
	}

	CPlayerState::Final_Tick();
}

void CPlayerRightMoveState::Enter()
{
	GET_PLAYER();

	pPlayer->SetFaceDir(true);

	if (pPlayer->IsFaceDirChange())
	{
		SetAnim(pPlayer->GetAnimator()->FindAnimation(L"Turn_Right"));
		pPlayer->GetAnimator()->Play(L"Turn_Right", false);
	}
	else
	{
		SetAnim(pPlayer->GetAnimator()->FindAnimation(L"Walk_Start_Right"));
		pPlayer->GetAnimator()->Play(L"Walk_Start_Right", false);
	}
}

void CPlayerRightMoveState::Exit()
{
	CPlayerState::Exit();
}