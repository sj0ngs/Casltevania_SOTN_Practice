#include "pch.h"
#include "CPlayerLeftMoveState.h"

#include "CPlayer.h"

CPlayerMoveLeftState::CPlayerMoveLeftState()
{
}

CPlayerMoveLeftState::~CPlayerMoveLeftState()
{
}

void CPlayerMoveLeftState::Final_Tick()
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
	else if(IS_TAP(EKEY::DOWN))
		ChangeState(L"Duck");
	else if (IS_TAP(EKEY::LSHIFT))
		ChangeState(L"BackDash");
	else if (IS_TAP(EKEY::RIGHT))
	{
		ChangeState(L"Move_Right");
	}
	else if(IS_RELEASED(EKEY::LEFT))
	{
		if (GetAnim()->IsFinish())
			ChangeState(L"MoveEnd");
		else 
			ChangeState(L"Idle");
	}
	/*else
		Hit();*/
	
	if (IS_PRESSED(EKEY::LEFT))
	{
		if (GetAnim()->IsFinish())
		{
			pPlayer->GetAnimator()->Play(L"Walk_Left", true);
		}

		Vec2 vPos = pPlayer->GetPos();
		Vec2 vDir = pPlayer->GetDir();
		float fSpeed = pPlayer->GetPlayerInfo().m_fSpeed;

		vPos -= vDir * fSpeed * DELTATIME;
		pPlayer->SetPos(vPos);
	}

	CPlayerState::Final_Tick();
}

void CPlayerMoveLeftState::Enter()
{
	GET_PLAYER();

	pPlayer->SetFaceDir(false);

	if (pPlayer->IsFaceDirChange())
	{
		SetAnim(pPlayer->GetAnimator()->FindAnimation(L"Turn_Left"));
		pPlayer->GetAnimator()->Play(L"Turn_Left", false);
	}
	else
	{
		SetAnim(pPlayer->GetAnimator()->FindAnimation(L"Walk_Start_Left"));
		pPlayer->GetAnimator()->Play(L"Walk_Start_Left", false);
	}
}

void CPlayerMoveLeftState::Exit()
{
	CPlayerState::Exit();
}