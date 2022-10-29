#include "pch.h"
#include "CPlayerFallState.h"

#include "CPlayer.h"

CPlayerFallState::CPlayerFallState()
{
}

CPlayerFallState::~CPlayerFallState()
{
}

void CPlayerFallState::Final_Tick()
{
	GET_PLAYER();

	CPlayerState::Final_Tick();

	if (pPlayer->GetRigidBody()->IsGround())
	{
		ChangeState(L"Landing");
	}
}

void CPlayerFallState::Enter()
{
	GET_PLAYER();
	
	if (pPlayer->GetFaceDir())
	{
		SET_ANIM(L"Fall_Right");
	}
	else
	{
		SET_ANIM(L"Fall_Left");
	}

	pPlayer->GetRigidBody()->SetGravity(true);
	pPlayer->GetRigidBody()->OffGround();
}

void CPlayerFallState::Exit()
{
	CPlayerState::Exit();
}
