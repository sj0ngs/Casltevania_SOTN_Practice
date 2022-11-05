#include "pch.h"
#include "CAttackState.h"

#include "CMonster.h"

CAttackState::CAttackState()
{
}

CAttackState::~CAttackState()
{
}

void CAttackState::Final_Tick()
{
	GET_MON();

	if (!pMon->IsAttack())
		ChangeState(L"Trace");

	Dead();
}

void CAttackState::Enter()
{
	GET_MON();

	pMon->Attack();
}

void CAttackState::Exit()
{
}
