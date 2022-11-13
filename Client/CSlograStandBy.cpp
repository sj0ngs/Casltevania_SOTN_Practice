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
