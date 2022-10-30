#include "pch.h"
#include "CPlayerState.h"

#include "CPlayer.h"

CPlayerState::CPlayerState()	:
	m_pAnim(nullptr)
{
}

CPlayerState::~CPlayerState()
{
}

void CPlayerState::Final_Tick()
{
	Move();
}

void CPlayerState::Exit()
{
	SetAnim(nullptr);
}

void CPlayerState::Move()
{
	GET_PLAYER();

	Vec2 vPos = pPlayer->GetPos();
	Vec2 vDir = pPlayer->GetDir();
	float fSpeed = pPlayer->GetSpeed();

	if (IS_PRESSED(EKEY::RIGHT))
	{
		vPos += vDir * fSpeed * DELTATIME;
	}
	else if (IS_PRESSED(EKEY::LEFT))
	{
		vPos -= vDir * fSpeed * DELTATIME;
	}

	pPlayer->SetPos(vPos);
}

void CPlayerState::Attack()
{
}
