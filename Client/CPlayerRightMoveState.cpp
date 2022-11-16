#include "pch.h"
#include "CPlayerRightMoveState.h"

#include "CPlayer.h"

CPlayerRightMoveState::CPlayerRightMoveState()
{
}

CPlayerRightMoveState::~CPlayerRightMoveState()
{
}

void CPlayerRightMoveState::Final_Tick()
{
	GET_PLAYER();

	if (IS_TAP(EKEY::A))
		Attack(L"StandAttack");
	else if (IS_TAP(EKEY::S))
		ChangeState(L"StandCover");
	else if (IS_TAP(EKEY::SPACE))
		ChangeState(L"Jump");
	else if (!pPlayer->GetRigidBody()->IsGround())
		ChangeState(L"Fall");
	else if (IS_TAP(EKEY::DOWN))
		ChangeState(L"Duck");
	else if (IS_TAP(EKEY::LSHIFT))
		ChangeState(L"BackDash");
	else if (IS_TAP(EKEY::LEFT))
	{
		ChangeState(L"Move_Left");
	}
	else if (IS_RELEASED(EKEY::RIGHT))
	{
		if (GetAnim()->IsFinish())
			ChangeState(L"MoveEnd");
		else
			ChangeState(L"Idle");
	}
	//else
	//	Hit();

	if (IS_PRESSED(EKEY::RIGHT))
	{
		if (GetAnim()->IsFinish())
		{
			pPlayer->GetAnimator()->Play(L"Walk_Right", true);
			//pPlayer->SetOnTrail(false);
		}

		Vec2 vPos = pPlayer->GetPos();
		Vec2 vDir = pPlayer->GetDir();
		float fSpeed = pPlayer->GetPlayerInfo().m_fSpeed;

		vPos += vDir * fSpeed * DELTATIME;
		pPlayer->SetPos(vPos);
	}

	CPlayerState::Final_Tick();
}

void CPlayerRightMoveState::Enter()
{
	GET_PLAYER();

	pPlayer->SetFaceDir(true);

	if (pPlayer->IsFaceDirChange())
	{
		SetAnim(pPlayer->GetAnimator()->FindAnimation(L"Turn_Right"));
		pPlayer->GetAnimator()->Play(L"Turn_Right", false);
	}
	else
	{
		SetAnim(pPlayer->GetAnimator()->FindAnimation(L"Walk_Start_Right"));
		pPlayer->GetAnimator()->Play(L"Walk_Start_Right", false);
	}

	pPlayer->SetOnTrail(true);
}

void CPlayerRightMoveState::Exit()
{
	GET_PLAYER();
	pPlayer->SetOnTrail(false);

	CPlayerState::Exit();
}