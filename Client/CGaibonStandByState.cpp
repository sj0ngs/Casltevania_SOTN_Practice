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
	// �ڽ��� ���� Monster �� �����´�
	GET_MON();

	// Player �� �˾Ƴ���
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->GetLayer(ELAYER::PLAYER)[0]);
	assert(pPlayer);

	// Player �� Monster �� �Ÿ����� ���
	float fDetectRange = pMon->GetMonsterInfo().m_fDetectRange;

	if (0 != fDetectRange)
	{
		// Player �� Ž������ �̳��� ������ ���� ���·� ��ȯ
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
