#include "pch.h"
#include "CPlayerGetUp.h"

#include "CPlayer.h"

CPlayerGetUp::CPlayerGetUp()
{
}

CPlayerGetUp::~CPlayerGetUp()
{
}

void CPlayerGetUp::Final_Tick()
{
	if (GetAnim()->IsFinish())
		ChangeState(L"Idle");
	else
	{
		if (IS_TAP(EKEY::RIGHT))
			ChangeState(L"Move_Right");
		else if (IS_TAP(EKEY::LEFT))
			ChangeState(L"Move_Left");
	}


	CPlayerState::Final_Tick();
	//Hit();
}

void CPlayerGetUp::Enter()
{
	GET_PLAYER();

	if (pPlayer->GetFaceDir())
	{
		SET_ANIM(L"Get_Up_Right");
	}
	else
	{
		SET_ANIM(L"Get_Up_Left");
	}
}

void CPlayerGetUp::Exit()
{
	CPlayerState::Exit();

	GET_PLAYER();
	pPlayer->GetUp();
}
