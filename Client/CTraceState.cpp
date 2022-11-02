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
	// �ڽ��� ���� Monster �� �����´�
	CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());
	assert(pMon);

	// Player �� �˾Ƴ���
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->GetLayer(ELAYER::PLAYER)[0]);

	// Player �� Monster �� �Ÿ����� ���
	float fDetectRange = pMon->GetMonsterInfo().m_fDetectRange;

	// Player �� Ž������ �̳��� ������ ���� ���·� ��ȯ
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
