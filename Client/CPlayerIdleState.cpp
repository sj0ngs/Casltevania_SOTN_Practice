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
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerObj());
	assert(pPlayer);

	CPlayerState::Final_Tick();

	if (IS_TAP(EKEY::LEFT))
	{
		ChangeState(L"Move_Left");
	}
	else if (IS_TAP(EKEY::RIGHT))
	{
		ChangeState(L"Move_Right");
	}
	else if (IS_TAP(EKEY::SPACE))
	{
		ChangeState(L"Jump");
	}
	else if (IS_TAP(EKEY::DOWN))
	{
		//ChangeState(L"Duck");
	}
	else if (!pPlayer->GetRigidBody()->IsGround())
	{
		//ChangeState(L"Fall");
	}
}

void CPlayerIdleState::Enter()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwnerObj());
	assert(pPlayer);

	if (pPlayer->GetFaceDir())
		pPlayer->GetAnimator()->Play(L"Idle_First_Right", true);
	else
		pPlayer->GetAnimator()->Play(L"Idle_First_Left", true);
}

void CPlayerIdleState::Exit()
{
}
