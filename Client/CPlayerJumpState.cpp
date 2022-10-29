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
	{
		ChangeState(L"Fall");
	}

	pPlayer->SetPos(vPos);

	CPlayerState::Final_Tick();
}

void CPlayerJumpState::Enter()
{
	GET_PLAYER();

	if (pPlayer->GetFaceDir())
	{
		if (IS_NONE(EKEY::LEFT)&&(IS_NONE(EKEY::RIGHT)))
		{
			SET_ANIM(L"Jump_Right");
		}
		else 
		{
			SET_ANIM(L"Jump_Foward_Right");
		}
	}
	else
	{
		if (IS_NONE(EKEY::LEFT) && (IS_NONE(EKEY::RIGHT)))
		{
			SET_ANIM(L"Jump_Left");
		}
		else
		{
			SET_ANIM(L"Jump_Foward_Left");
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
