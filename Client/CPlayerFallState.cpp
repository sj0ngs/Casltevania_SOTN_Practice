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
		pPlayer->ResetJump();
		ChangeState(L"Landing");
		return;
	}
	else
	{
		if (IS_TAP(EKEY::A))
		{
			Attack(L"JumpAttack");
			return;
		}

		if (IS_TAP(EKEY::SPACE))
		{
			if (pPlayer->CanDoubleJump())
			{
				pPlayer->OffDoubleJump();
				ChangeState(L"Jump");
				return;
			}
		}

		if (IS_TAP(EKEY::LEFT))
		{
			pPlayer->SetFaceDir(false);
			pPlayer->GetAnimator()->Shift(L"Fall_Left", false);
		}
		else if (IS_TAP(EKEY::RIGHT))
		{
			pPlayer->SetFaceDir(true);
			pPlayer->GetAnimator()->Shift(L"Fall_Right", false);
		}
	}

	Move();
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
