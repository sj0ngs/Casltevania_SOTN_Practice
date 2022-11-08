#include "pch.h"
#include "CTraceState.h"

#include "CLevelMgr.h"
#include "CTimeMgr.h"

#include "CLevel.h"

#include "CMonster.h"
#include "CPlayer.h"

CTraceState::CTraceState()	:
	m_bCanAttack(true),
	m_faccAttackCool(0.f)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Final_Tick()
{	
	// 자신의 소유 Monster 를 가져온다
	GET_MON();

	// Player 를 알아낸다
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->GetLayer(ELAYER::PLAYER)[0]);
	assert(pPlayer);

	// Player 와 Monster 의 거리값을 계산
	float fDetectRange = pMon->GetMonsterInfo().m_fDetectRange;

	// Player 가 탐지범위를 벗어나면
	Vec2 vDir = pPlayer->GetPos() - pMon->GetPos();
	if (fDetectRange < vDir.Length())
	{
		ChangeState(L"Idle");
		return;
	}

	float fAttackRange = pMon->GetMonsterInfo().m_fAttackRange;
	float fDodgeRange = pMon->GetMonsterInfo().m_fDodgeRange;

	if (m_bCanAttack && fAttackRange > vDir.Length() && fDodgeRange < vDir.Length())
	{
		ChangeState(L"Attack");
		m_bCanAttack = false;
		return;
	}

	if (!m_bCanAttack)
	{
		m_faccAttackCool += DELTATIME;

		float fAttackCoolTime = pMon->GetMonsterInfo().m_fAttackCoolTime;
		if (fAttackCoolTime <= m_faccAttackCool)
		{
			m_faccAttackCool = 0.f;
			m_bCanAttack = true;
		}
	}

	if (0 <= vDir.x)
	{
		if (!pMon->GetFaceDir())
			pMon->Turn();
	}
	else
	{
		if (pMon->GetFaceDir())
			pMon->Turn();
	}

	Vec2 vMonsterPos = pMon->GetPos();
	Vec2 vPlayerPos = pPlayer->GetPos();
	vDir = vPlayerPos - vMonsterPos;
	float fDist = vDir.Length();
	vDir.Normalize();
	 
	float fSpeed = pMon->GetMonsterInfo().m_fTraceSpeed;

	if(fDodgeRange >= fDist)
		vMonsterPos.x -= vDir.x * fSpeed * DELTATIME;
	else
		vMonsterPos.x += vDir.x * fSpeed * DELTATIME;

	pMon->SetPos(vMonsterPos);

	Dead();
}

void CTraceState::Enter()
{
	GET_MON();

	pMon->Walk();
}

void CTraceState::Exit()
{
}
