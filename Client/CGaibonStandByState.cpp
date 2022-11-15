#include "pch.h"
#include "CGaibonStandByState.h"

#include "CResMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CPlayer.h"
#include "CGaibon.h"

#include "CSound.h"

CGaibonStandByState::CGaibonStandByState()
{
}

CGaibonStandByState::~CGaibonStandByState()
{
}

void CGaibonStandByState::Final_Tick()
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
			ChangeState(L"GaibonMove");
			return;
		}
	}
}

void CGaibonStandByState::Enter()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	pGaibon->Walk();

	pGaibon->SetFly(true);
}

void CGaibonStandByState::Exit()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	pGaibon->Wake();

	CSound* pSound = CResMgr::GetInst()->FindSound(L"Festival_of_Servants");
	pSound->PlayToBGM(true);

	pGaibon->SetFly(false);
}
