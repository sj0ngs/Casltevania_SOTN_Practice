#include "pch.h"
#include "CPlayerIdleState.h"

#include "CPlayer.h"

CPlayerIdleState::CPlayerIdleState()
{
}

CPlayerIdleState::~CPlayerIdleState()
{
}

void CPlayerIdleState::Final_Tick()
{
	GET_PLAYER();

	if (IS_PRESSED(EKEY::SPACE))
	{
		ChangeState(L"Jump");
		return;
	}
	else if (IS_TAP(EKEY::A))
	{
		Attack(L"StandAttack");
		return;
	}
	else if (IS_TAP(EKEY::S))
	{
		ChangeState(L"StandCover");
		return;
	}
	else if (IS_PRESSED(EKEY::DOWN))
	{
		ChangeState(L"Duck");
		return;
	}
	else if (IS_PRESSED(EKEY::LSHIFT))
	{
		ChangeState(L"BackDash");
		return;
	}

	if (IS_PRESSED(EKEY::LEFT))
	{
		ChangeState(L"Move_Left");
	}
	else if (IS_PRESSED(EKEY::RIGHT))
	{
		ChangeState(L"Move_Right");
	}
	else if (IS_PRESSED(EKEY::UP))
	{
		if (pPlayer->GetFaceDir())
			pPlayer->GetAnimator()->Play(L"Press_Up_Right", false);
		else
			pPlayer->GetAnimator()->Play(L"Press_Up_Left", false);
	}
	else if (IS_RELEASED(EKEY::UP))
	{
		if (pPlayer->GetFaceDir())
			pPlayer->GetAnimator()->Play(L"Idle_First_Right", false);
		else
			pPlayer->GetAnimator()->Play(L"Idle_First_Left", false);
	}

	CPlayerState::Final_Tick();;

	//Hit();
}

void CPlayerIdleState::Enter()
{
	GET_PLAYER();

	if (pPlayer->GetFaceDir())
		pPlayer->GetAnimator()->Play(L"Idle_First_Right", true);
	else
		pPlayer->GetAnimator()->Play(L"Idle_First_Left", true);
}

void CPlayerIdleState::Exit()
{
}
