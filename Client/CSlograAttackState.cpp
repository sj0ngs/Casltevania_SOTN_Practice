#include "pch.h"
#include "CSlograAttackState.h"

#include "CMonster.h"

CSlograAttackState::CSlograAttackState()
{
}

CSlograAttackState::~CSlograAttackState()
{
}

void CSlograAttackState::Final_Tick()
{
	GET_MON();

	if (!pMon->IsAttack())
		ChangeState(L"SlograMove");

	Dead();
}

void CSlograAttackState::Enter()
{
	GET_MON();

	pMon->Attack();
}

void CSlograAttackState::Exit()
{
}
