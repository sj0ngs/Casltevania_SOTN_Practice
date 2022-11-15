#include "pch.h"
#include "CPlayerDeathState.h"

#include "CPlayer.h"

CPlayerDeathState::CPlayerDeathState()
{
}

CPlayerDeathState::~CPlayerDeathState()
{
}

void CPlayerDeathState::Final_Tick()
{
	if (GetAnim()->IsFinish())
	{
		ChangeLevel(ELEVEL_TYPE::GAME_OVER);
		GET_PLAYER();

		pPlayer->Revive();
	}
}

void CPlayerDeathState::Enter()
{
	GET_PLAYER();

	SET_ANIM(L"Hit_6_Left");
}

void CPlayerDeathState::Exit()
{
}
