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

void CPlayerAttackState::Enter()
{

}

void CPlayerAttackState::Exit()
{
	GET_PLAYER();

	CPlayerState::Exit();
	m_pAttack->SetDead();
	m_pAttack = nullptr;

	if (nullptr != pPlayer->GetWeapon())
		pPlayer->GetWeapon()->AttackEnd();
}
