#include "pch.h"
#include "CGaibonMoveState.h"

#include "CResMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CPlayer.h"
#include "CGaibon.h"
#include "CSlogra.h"

#include "CSound.h"

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
	
	//Vec2 vPrevPos = pGaibon->GetPrevPos();

	if (1.f >= fDist || !pGaibon->IsFly())
	{
		ChangeState(L"GaibonSkyAttack");
		return;
	}

	vDist.Normalize();

	float fSpeed = pGaibon->GetMonsterInfo().m_fTraceSpeed;

	vMonPos.x += vDist.x * fSpeed * DELTATIME;
	vMonPos.y += vDist.y * fSpeed * DELTATIME;

	pGaibon->SetPos(vMonPos);

	if (pGaibon->GetSlogra())
	{
		CSlogra* pSlogra = pGaibon->GetSlogra();

		if (pSlogra->IsSlograHit())
		{
			ChangeState(L"GaibonTraceSlogra");
		}
	}

	Dead();
}

void CGaibonMoveState::Enter()
{
	GET_PLAYER();
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	pGaibon->GetCollider()->SetScale(Vec2(70.f, 150.f));
	pGaibon->GetCollider()->SetOffsetPos(Vec2(0.f, -145.f));
	pGaibon->Walk();

	// Move State 로 들어올 때 플레이어 위치의 근처의 랜덤한 장소를 목적지로 설정한다
	Vec2 vPos = pPlayer->GetPos();
	Vec2 vPrevPos = pPlayer->GetPrevPos();

	float fGaibonDir = vPos.x - pGaibon->GetPos().x;
	float fPlayerDir = vPos.x - vPrevPos.x;

	if (0 < fGaibonDir)
	{
		vPos.x += 200.f;
	}
	else if(0 > fGaibonDir)
	{
		vPos.x -= 200.f;
	}

	if (0 < fPlayerDir)
	{
		vPos.x += 200.f;
	}
	else if (0 > fPlayerDir)
	{
		vPos.x -= 200.f;
	}

	vPos.y -=  200.f;

	vDest = vPos;

	CSound* pSound = CResMgr::GetInst()->FindSound(L"Gaibon_Flap");
	pSound->Play(true);

	pGaibon->SetFly(true);
}

void CGaibonMoveState::Exit()
{
	CGaibon* pGaibon = (CGaibon*)GetOwnerObj();

	vDest = Vec2(0.f, 0.f);

	CSound* pSound = CResMgr::GetInst()->FindSound(L"Gaibon_Flap");
	pSound->Stop();

	pGaibon->SetFly(false);
}
