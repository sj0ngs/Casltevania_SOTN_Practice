#include "pch.h"
#include "CMonsterState.h"

#include "CMonster.h"

CMonsterState::CMonsterState()
{
}

CMonsterState::~CMonsterState()
{
}

void CMonsterState::Final_Tick()
{
}

void CMonsterState::Exit()
{
}

void CMonsterState::Dead()
{
	GET_MON();

	if (0 == pMon->GetMonsterInfo().m_iHP)
		ChangeState(L"Dead");
}
