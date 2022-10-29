#include "pch.h"
#include "CPlayerMoveEndState.h"

#include "CPlayer.h"

CPlayerMoveEndState::CPlayerMoveEndState()
{
}

CPlayerMoveEndState::~CPlayerMoveEndState()
{
}

void CPlayerMoveEndState::Final_Tick()
{
	assert(GetAnim());

	if (GetAnim()->IsFinish())
		ChangeState(L"Idle");
	else if (IS_TAP(EKEY::LEFT))
		ChangeState(L"Move_Left");
	else if (IS_TAP(EKEY::RIGHT))
		ChangeState(L"Move_Right");
}

void CPlayerMoveEndState::Enter()
{
	GET_PLAYER();

	if (pPlayer->GetFaceDir())
	{
		SetAnim(pPlayer->GetAnimator()->FindAnimation(L"Walk_End_Right"));
		pPlayer->GetAnimator()->Play(L"Walk_End_Right", false);
	}
	else
	{
		SetAnim(pPlayer->GetAnimator()->FindAnimation(L"Walk_End_Left"));
		pPlayer->GetAnimator()->Play(L"Walk_End_Left", false);
	}
}

void CPlayerMoveEndState::Exit()
{
	CPlayerState::Exit();
}
