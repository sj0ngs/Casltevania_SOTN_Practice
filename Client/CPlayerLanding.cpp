#include "pch.h"
#include "CPlayerLanding.h"

#include "CPlayer.h"

CPlayerLanding::CPlayerLanding()
{
}

CPlayerLanding::~CPlayerLanding()
{
}

void CPlayerLanding::Final_Tick()
{
	if (GetAnim()->IsFinish())
	{
		ChangeState(L"Idle");
	}
	else if (IS_PRESSED(EKEY::RIGHT))
		ChangeState(L"Move_Right");
	else if (IS_PRESSED(EKEY::LEFT))
		ChangeState(L"Move_Left");
}

void CPlayerLanding::Enter()
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

void CPlayerLanding::Exit()
{
	CPlayerState::Exit();
}
