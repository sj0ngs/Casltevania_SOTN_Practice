#include "pch.h"
#include "CPlayerState.h"

#include "CPlayer.h"
#include "CWeapon.h"

CPlayerState::CPlayerState()	:
	m_pAnim(nullptr)
{
}

CPlayerState::~CPlayerState()
{
}

void CPlayerState::Final_Tick()
{
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
	float fSpeed = pPlayer->GetPlayerInfo().m_fSpeed;

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

void CPlayerState::Attack(const wchar_t* strState)
{
	GET_PLAYER();

	if (pPlayer->Attack())
	{
		if(pPlayer->GetWeapon())
			pPlayer->GetWeapon()->Attack(pPlayer->GetFaceDir());

		ChangeState(strState);
	}
}
