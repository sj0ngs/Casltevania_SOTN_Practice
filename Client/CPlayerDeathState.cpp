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
		ChangeLevel(ELEVEL_TYPE::EDITOR);
}

void CPlayerDeathState::Enter()
{
	GET_PLAYER();

	SET_ANIM(L"Hit_6_Left");
}

void CPlayerDeathState::Exit()
{
}
