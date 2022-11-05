#include "pch.h"
#include "CTraceState.h"

#include "CLevelMgr.h"
#include "CTimeMgr.h"

#include "CLevel.h"

#include "CMonster.h"
#include "CPlayer.h"
CTraceState::CTraceState()
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

	if (fAttackRange > vDir.Length())
	{
		ChangeState(L"Attack");
		return;
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
	vDir.Normalize();
	 
	float fSpeed = pMon->GetMonsterInfo().m_fTraceSpeed;
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
