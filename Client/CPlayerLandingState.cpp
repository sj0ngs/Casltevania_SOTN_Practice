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
		ChangeState(L"Idle");
	else if (IS_TAP(EKEY::A))
		Attack(L"StandAttack");
	else if (IS_TAP(EKEY::SPACE))
		ChangeState(L"Jump");
	else if (IS_PRESSED(EKEY::RIGHT))
		ChangeState(L"Move_Right");
	else if (IS_PRESSED(EKEY::LEFT))
		ChangeState(L"Move_Left");
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
}

void CPlayerLandingState::Exit()
{
	CPlayerState::Exit();
}
