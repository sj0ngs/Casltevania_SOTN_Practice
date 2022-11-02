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
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);

	// Player 를 알아낸다
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->GetLayer(ELAYER::PLAYER)[0]);

	// Player 와 Monster 의 거리값을 계산
	float fDetectRange = pMon->GetMonsterInfo().m_fDetectRange;

	// Player 가 탐지범위 이내에 들어오면 추적 상태로 전환
	Vec2 vDir = pPlayer->GetPos() - pMon->GetPos();
	if (fDetectRange < vDir.Length())
	{
		ChangeState(L"Idle");
		return;
	}

	Vec2 vMonsterPos = pMon->GetPos();
	Vec2 vPlayerPos = pPlayer->GetPos();
	vDir = vPlayerPos - vMonsterPos;
	vDir.Normalize();
	 
	float fSpeed = pMon->GetMonsterInfo().m_fSpeed;

	vMonsterPos += vDir * fSpeed * DELTATIME;

	pMon->SetPos(vMonsterPos);
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
