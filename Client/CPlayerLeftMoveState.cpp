#include "pch.h"
#include "CPlayerLeftMoveState.h"

#include "CPlayer.h"

CPlayerMoveLeftState::CPlayerMoveLeftState()
{
}

CPlayerMoveLeftState::~CPlayerMoveLeftState()
{
}

void CPlayerMoveLeftState::Final_Tick()
{
	GET_PLAYER();

	if (IS_TAP(EKEY::SPACE))
	{
		ChangeState(L"Jump");
	}

	if (IS_TAP(EKEY::RIGHT))
	{
		ChangeState(L"Move_Right");
		return;
	}
	else if (IS_PRESSED(EKEY::LEFT))
	{
		if (GetAnim()->IsFinish())
		{
			pPlayer->GetAnimator()->Play(L"Walk_Left", true);
		}
	}
	else if(IS_RELEASED(EKEY::LEFT))
	{
		if (GetAnim()->IsFinish())
			ChangeState(L"MoveEnd");
		else 
			ChangeState(L"Idle");
	}

	CPlayerState::Final_Tick();
}

void CPlayerMoveLeftState::Enter()
{
	GET_PLAYER();

	pPlayer->SetFaceDir(false);

	if (pPlayer->IsFaceDirChange())
	{
		SetAnim(pPlayer->GetAnimator()->FindAnimation(L"Turn_Left"));
		pPlayer->GetAnimator()->Play(L"Turn_Left", false);
	}
	else
	{
		SetAnim(pPlayer->GetAnimator()->FindAnimation(L"Walk_Start_Left"));
		pPlayer->GetAnimator()->Play(L"Walk_Start_Left", false);
	}
}

void CPlayerMoveLeftState::Exit()
{
	CPlayerState::Exit();
}