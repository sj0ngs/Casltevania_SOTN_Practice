#include "pch.h"
#include "CSlograStandBy.h"

#include "CLevelMgr.h"

#include "CLevel.h"

#include "CSlogra.h"

#include "CPlayer.h"

CSlograStandBy::CSlograStandBy()
{
}

CSlograStandBy::~CSlograStandBy()
{
}

void CSlograStandBy::Final_Tick()
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
			ChangeState(L"SlograMove");
			return;
		}
	}
}

void CSlograStandBy::Enter()
{
	CSlogra* pSlogra = (CSlogra*)GetOwnerObj();

	pSlogra->Idle();
}

void CSlograStandBy::Exit()
{
}
