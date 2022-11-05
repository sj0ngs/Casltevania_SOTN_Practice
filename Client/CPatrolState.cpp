#include "pch.h"
#include "CPatrolState.h"

#include "CMonster.h"

CPatrolState::CPatrolState()	:
	m_faccTime(0.f)
{
}

CPatrolState::~CPatrolState()
{
}

void CPatrolState::Final_Tick()
{
	GET_MON();

	// ¼øÂû ·ÎÁ÷	- ÁÂ¿ì ¿Ô´Ù °¬´Ù
	Vec2 vPos = pMon->GetPos();

	if (pMon->GetFaceDir())
	{
		vPos.x += pMon->GetMonsterInfo().m_fPatrolSpeed * DELTATIME;
	}
	else
	{
		vPos.x -= pMon->GetMonsterInfo().m_fPatrolSpeed * DELTATIME;
	}

	if (3.f <= m_faccTime)
	{
		pMon->Turn();
		m_faccTime = 0.f;
	}

	m_faccTime += DELTATIME;
	pMon->SetPos(vPos);

	Dead();
}

void CPatrolState::Enter()
{
	GET_MON();

	pMon->Walk();
}

void CPatrolState::Exit()
{
}
