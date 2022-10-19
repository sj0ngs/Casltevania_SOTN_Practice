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
	// �ڽ��� ���� Monster �� �����´�
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);

	// Player �� �˾Ƴ���
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->GetLayer(ELAYER::PLAYER)[0]);
	assert(pPlayer);

	// Player �� Monster �� �Ÿ����� ���
	float fDetectRange = pMon->GetMonsterInfo().m_fDetectRange;

	// Player �� Ž������ �̳��� ������ ���� ���·� ��ȯ
	Vec2 vDir = pMon->GetPos() - pPlayer->GetPos();
	if (fDetectRange > vDir.Length())
	{
		ChangeState(L"Trace");
	}
}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}
