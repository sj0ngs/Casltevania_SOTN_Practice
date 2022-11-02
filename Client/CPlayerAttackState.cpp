#include "pch.h"
#include "CPlayerAttackState.h"

#include "CPlayer.h"
#include "CWeapon.h"

CPlayerAttackState::CPlayerAttackState()	:
	m_pAttack(nullptr)
{
}

CPlayerAttackState::~CPlayerAttackState()
{
}

void CPlayerAttackState::Exit()
{
	GET_PLAYER();

	CPlayerState::Exit();

	if (IsValid((CObj*&)m_pAttack))
	{
		m_pAttack->SetDead();
		m_pAttack = nullptr;
	}

	if (nullptr != pPlayer->GetWeapon())
		pPlayer->GetWeapon()->AttackEnd();
}
