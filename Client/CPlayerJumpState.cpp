#include "pch.h"
#include "CPlayerJumpState.h"

#include "CPlayer.h"

CPlayerJumpState::CPlayerJumpState()	:
	m_accJumpTime(0.f)
{
}

CPlayerJumpState::~CPlayerJumpState()
{
}

void CPlayerJumpState::Final_Tick()
{
	GET_PLAYER();

	Vec2 vPos = pPlayer->GetPos();

	m_accJumpTime += DELTATIME;

	if (IS_PRESSED(EKEY::SPACE) && 0.5f >= m_accJumpTime)
	{
		vPos.y -= 600.f * DELTATIME;
	}
	else
		ChangeState(L"Fall");

	if (IS_TAP(EKEY::LEFT))
	{
		pPlayer->SetFaceDir(false);
		pPlayer->GetAnimator()->Shift(L"Jump_Foward_Left", false);
	}
	else if (IS_TAP(EKEY::RIGHT))
	{
		pPlayer->SetFaceDir(true);
		pPlayer->GetAnimator()->Shift(L"Jump_Foward_Right", false);
	}

	pPlayer->SetPos(vPos);

	CPlayerState::Final_Tick();
}

void CPlayerJumpState::Enter()
{
	GET_PLAYER();

	if (pPlayer->GetFaceDir())
	{
		if (pPlayer->CanDoubleJump())
		{
			if (IS_NONE(EKEY::LEFT) && (IS_NONE(EKEY::RIGHT)))
				pPlayer->GetAnimator()->Play(L"Jump_Right", false);
			else
				pPlayer->GetAnimator()->Play(L"Jump_Foward_Right", false);
		}
		else
		{
			Vec2 vVelocity = pPlayer->GetRigidBody()->GetVelocity();
			pPlayer->GetRigidBody()->AddVelocity(Vec2(0.f, -vVelocity.y));
			pPlayer->GetAnimator()->Play(L"Double_Jump_Right", false);
		}
	}
	else
	{
		if (pPlayer->CanDoubleJump())
		{
			if (IS_NONE(EKEY::LEFT) && (IS_NONE(EKEY::RIGHT)))
				pPlayer->GetAnimator()->Play(L"Jump_Left", false);
			else
				pPlayer->GetAnimator()->Play(L"Jump_Foward_Left", false);
		}
		else
		{
			Vec2 vVelocity = pPlayer->GetRigidBody()->GetVelocity();
			pPlayer->GetRigidBody()->AddVelocity(Vec2(0.f, -vVelocity.y));
			pPlayer->GetAnimator()->Play(L"Double_Jump_Left", false);
		}

	}

	pPlayer->GetRigidBody()->SetGravity(false);
	pPlayer->GetRigidBody()->OffGround();
}

void CPlayerJumpState::Exit()
{
	SetAnim(nullptr);
	m_accJumpTime = 0.f;
}
