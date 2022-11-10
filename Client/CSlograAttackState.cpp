#include "pch.h"
#include "CSlograAttackState.h"

#include "CSlogra.h"

CSlograAttackState::CSlograAttackState()
{
}

CSlograAttackState::~CSlograAttackState()
{
}

void CSlograAttackState::Final_Tick()
{
	CSlogra* pSlogra = (CSlogra*)GetOwnerObj();

	if (!pSlogra->IsAttack())
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
