#include "pch.h"
#include "CSlograIdleState.h"

#include "CTimeMgr.h"

#include "CMonster.h"

CSlograIdleState::CSlograIdleState() :
	m_fStopTime(0.f),
	m_faccStopTime(0.f)
{
}

CSlograIdleState::~CSlograIdleState()
{
}

void CSlograIdleState::Final_Tick()
{
	m_faccStopTime += DELTATIME;

	if (m_fStopTime <= m_faccStopTime)
		ChangeState(L"SlograMove");
}

void CSlograIdleState::Enter()
{
	GET_MON();

	pMon->Idle();
	m_fStopTime = 0.5f;
}

void CSlograIdleState::Exit()
{
	m_fStopTime = 0.f;
	m_faccStopTime = 0.f;
}
