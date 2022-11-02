#include "pch.h"
#include "CPlayerLandingState.h"

#include "CPlayer.h"

CPlayerLandingState::CPlayerLandingState()
{
}

CPlayerLandingState::~CPlayerLandingState()
{
}

void CPlayerLandingState::Final_Tick()
{	
	if (GetAnim()->IsFinish())
	{
		ChangeState(L"Idle");
		return;
	}
	else if (IS_TAP(EKEY::A))
	{
		Attack(L"StandAttack");
		return;
	}
	else if (IS_TAP(EKEY::SPACE))
	{
		ChangeState(L"Jump");
		return;
	}
	else if (IS_PRESSED(EKEY::RIGHT))
	{
		ChangeState(L"Move_Right");
		return;
	}
	else if (IS_PRESSED(EKEY::LEFT))
	{
		ChangeState(L"Move_Left");
		return;
	}
	//else
	//	Hit();

	CPlayerState::Final_Tick();
}

void CPlayerLandingState::Enter()
{
	GET_PLAYER();

	if (pPlayer->GetFaceDir())
	{
		SET_ANIM(L"Landing_Right");
	}
	else
	{
		SET_ANIM(L"Landing_Left");
	}

	pPlayer->ResetJump();
}

void CPlayerLandingState::Exit()
{
	CPlayerState::Exit();
}
