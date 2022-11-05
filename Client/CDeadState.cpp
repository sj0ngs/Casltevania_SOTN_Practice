#include "pch.h"
#include "CDeadState.h"

#include "CMonster.h"

CDeadState::CDeadState()
{
}

CDeadState::~CDeadState()
{
}

void CDeadState::Final_Tick()
{
}

void CDeadState::Enter()
{
	GET_MON();

	pMon->Dead();
}

void CDeadState::Exit()
{
}
