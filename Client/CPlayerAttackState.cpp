#include "pch.h"
#include "CPlayerAttackState.h"

#include "CPlayer.h"

CPlayerAttackState::CPlayerAttackState()
{
}

CPlayerAttackState::~CPlayerAttackState()
{
}

void CPlayerAttackState::Final_Tick()
{
	GET_PLAYER();

	if (nullptr != GetAnim())
	{
		if (GetAnim()->IsFinish())
		{
			ChangeState(L"Idle");
		}
	}
}

void CPlayerAttackState::Enter()
{
	GET_PLAYER();

	if (pPlayer->GetFaceDir())
	{
		SET_ANIM(L"Stand_Attack_Default_Right");
	}
	else
	{
		SET_ANIM(L"Stand_Attack_Default_Left");
	}
}

void CPlayerAttackState::Exit()
{
	CPlayerState::Exit();
}
