#include "pch.h"
#include "CMonsterAttack.h"

#include "CTimeMgr.h"

#include "CPlayer.h"

CMonsterAttack::CMonsterAttack()	:
	m_faccLifeTime(0.f),
	m_fLifeSpan(0.f)
{
}

CMonsterAttack::~CMonsterAttack()
{
}

void CMonsterAttack::Tick()
{
	CObj::Tick();

	if (m_fLifeSpan <= m_faccLifeTime)
	{
		SetDead();
		return;
	}

	m_faccLifeTime += DELTATIME;
}

void CMonsterAttack::Render(HDC _DC)
{
	CObj::Render(_DC);
}

