#include "pch.h"
#include "CGaibonMoveState.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CPlayer.h"
#include "CGaibon.h"

CGaibonMoveState::CGaibonMoveState()	:
	vDest(0.f, 0.f)
{
}

CGaibonMoveState::~CGaibonMoveState()
{
}

void CGaibonMoveState::Final_Tick()
{
	GET_PLAYER();
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	// 바라보는 방향 전환
	Vec2 vDir = pPlayer->GetPos() - pGaibon->GetPos();

	if (0 <= vDir.x)
	{
		if (!pGaibon->GetFaceDir())
			pGaibon->Turn();
	}
	else
	{
		if (pGaibon->GetFaceDir())
			pGaibon->Turn();
	}

	Vec2 vMonPos = pGaibon->GetPos();
	Vec2 vDist = vDest - vMonPos;
	float fDist = vDist.Length();
	
	Vec2 vPrevPos = pGaibon->GetPrevPos();

	if (0.1f >= fDist)
	{
		ChangeState(L"GaibonSkyAttack");
		return;
	}

	vDist.Normalize();

	float fSpeed = pGaibon->GetMonsterInfo().m_fTraceSpeed;

	vMonPos.x += vDist.x * fSpeed * DELTATIME;
	vMonPos.y += vDist.y * fSpeed * DELTATIME;

	pGaibon->SetPos(vMonPos);

	Dead();
}

void CGaibonMoveState::Enter()
{
	GET_PLAYER();
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	pGaibon->Walk();

	// Move State 로 들어올 때 플레이어 위치의 근처의 랜덤한 장소를 목적지로 설정한다
	Vec2 vPos = pPlayer->GetPos();
	Vec2 vPrevPos = pPlayer->GetPrevPos();

	float fPlayerDir = vPos.x - vPrevPos.y;

	if (pGaibon->GetFaceDir())
	{
		vPos.x += 100.f;
	}
	else
	{
		vPos.x -= 100.f;
	}

	if (0 < fPlayerDir)
	{
		vPos.x += 100.f;
	}
	else if (0 > fPlayerDir)
	{
		vPos.x -= 100.f;
	}

	vPos.y -=  300.f;

	vDest = vPos;
}

void CGaibonMoveState::Exit()
{
	vDest = Vec2(0.f, 0.f);
}
