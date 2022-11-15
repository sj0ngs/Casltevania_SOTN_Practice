#include "pch.h"
#include "CPlayerAttackState.h"

#include "CResMgr.h"

#include "CSound.h"

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
	LARGE_INTEGER llCount;
	QueryPerformanceCounter(&llCount);
	srand((UINT)llCount.QuadPart);
	int iRand = rand();

	iRand = rand() % 6;

	CSound* pSound = nullptr;

	switch (iRand)
	{
	case 0:
		pSound = CResMgr::GetInst()->FindSound(L"ATTACK_01");
		break;
	case 1:
		pSound = CResMgr::GetInst()->FindSound(L"ATTACK_02");
		break;
	case 2:
		pSound = CResMgr::GetInst()->FindSound(L"ATTACK_03");
		break;
	case 3:
		pSound = CResMgr::GetInst()->FindSound(L"ATTACK_04");
		break;
	case 4:
		pSound = CResMgr::GetInst()->FindSound(L"ATTACK_05");
		break;
	case 5:
		pSound = CResMgr::GetInst()->FindSound(L"ATTACK_06");
		break;
	}

	pSound->Play();
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
