#include "pch.h"
#include "CIdleState.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster.h"
#include "CPlayer.h"

CIdleState::CIdleState()
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Final_Tick()
{
	// 자신의 소유 Monster 를 가져온다
	GET_MON();

	// Player 를 알아낸다
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->GetLayer(ELAYER::PLAYER)[0]);
	assert(pPlayer);

	// Player 와 Monster 의 거리값을 계산
	float fDetectRange = pMon->GetMonsterInfo().m_fDetectRange;

	if (0 != fDetectRange)
	{
		// Player 가 탐지범위 이내에 들어오면 추적 상태로 전환
		Vec2 vDir = pMon->GetPos() - pPlayer->GetPos();
		if (fDetectRange > vDir.Length())
		{
			ChangeState(L"Trace");
			return;
		}
	}

	Dead();
}

void CIdleState::Enter()
{
	GET_MON();

	pMon->Idle();
}

void CIdleState::Exit()
{
}
