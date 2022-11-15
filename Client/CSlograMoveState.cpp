#include "pch.h"
#include "CSlograMoveState.h"

#include "CLevelMgr.h"

#include "CLevel.h"

#include "CPlayer.h"
#include "CSlogra.h"

#include "CAnimator.h"

CSlograMoveState::CSlograMoveState()
{
}

CSlograMoveState::~CSlograMoveState()
{
}

void CSlograMoveState::Final_Tick()
{
	GET_PLAYER();

	CSlogra* pSlogra = (CSlogra*)GetOwnerObj();
	
	Vec2 vDir = pPlayer->GetPos() - pSlogra->GetPos();

	if (0 <= vDir.x)
	{
		if (!pSlogra->GetFaceDir())
			pSlogra->Turn();
	}
	else
	{
		if (pSlogra->GetFaceDir())
			pSlogra->Turn();
	}

	float fAttackRange = pSlogra->GetMonsterInfo().m_fAttackRange;

	if (pSlogra->SlograCanAttack() &&  fAttackRange > vDir.Length())
	{
		ChangeState(L"SlograAttack");
		return;
	}
	else if (ESLOGRA_STATE::SPEAR == pSlogra->GetSlograState() && pSlogra->SlograCanFire())
	{
		ChangeState(L"SlograFire");
		return;
	}

	//LARGE_INTEGER llCount;
	//QueryPerformanceCounter(&llCount);
	//srand((UINT)llCount.QuadPart);
	srand((UINT)time(0));

	int iRand = rand();
 	iRand = rand() % 100 + 1;

	if (1 >= iRand)
	{
		ChangeState(L"SlograIdle");
	}
	else
	{
		Vec2 vMonsterPos = pSlogra->GetPos();
		Vec2 vPlayerPos = pPlayer->GetPos();
		vDir = vPlayerPos - vMonsterPos;
		float fDist = vDir.Length();
		vDir.Normalize();

		float fSpeed = pSlogra->GetMonsterInfo().m_fTraceSpeed;

		if (30 >= iRand)
		{
			vMonsterPos.x -= vDir.x * fSpeed * DELTATIME;
		}
		else
		{
			vMonsterPos.x += vDir.x * fSpeed * DELTATIME;
		}

		pSlogra->SetPos(vMonsterPos);
	}

	Dead();
}

void CSlograMoveState::Enter()
{
	GET_MON();

	pMon->Walk();
}

void CSlograMoveState::Exit()
{
}
