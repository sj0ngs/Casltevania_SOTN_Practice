#include "pch.h"
#include "CPlayerDeathState.h"

#include "CResMgr.h"

#include "CPlayer.h"

#include "CSound.h"

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

	SET_ANIM(L"Alucrad_Death");

	PLAY_SOUND(L"DIE");

	CCamera::GetInst()->FadeOut(11.f);
}

void CPlayerDeathState::Exit()
{
}
