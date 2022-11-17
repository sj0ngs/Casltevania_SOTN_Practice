#include "pch.h"
#include "CPlayerHitState.h"

#include "CResMgr.h"

#include "CPlayer.h"

#include "CSound.h"

CPlayerHitState::CPlayerHitState()
{
}

CPlayerHitState::~CPlayerHitState()
{
}

void CPlayerHitState::Final_Tick()
{
	GET_PLAYER();

	if (pPlayer->GetRigidBody()->IsGround())
		ChangeState(L"Landing");

	Dead();
}

void CPlayerHitState::Enter()
{
	GET_PLAYER();

	// 오른쪽으로 맞았을 때
	if (pPlayer->GetFaceDir())
	{
		SET_ANIM(L"Hit_6_Right");
		pPlayer->GetRigidBody()->SetVelocity(Vec2(-300.f, -500.f));
	}
	// 왼쪽으로 맞았을 때
	else
	{
		SET_ANIM(L"Hit_6_Left");
		pPlayer->GetRigidBody()->SetVelocity(Vec2(300.f, -500.f));
	}

	pPlayer->GetRigidBody()->OffGround();
	pPlayer->GetRigidBody()->SetGravity(true);
	pPlayer->GetUp();

	HitSound();

	//pPlayer->GetAnimator()->SetAnimOpt(EANIM_OPT::ALPHA_BLEND);
}

void CPlayerHitState::Exit()
{
	GET_PLAYER();
	CPlayerState::Exit();
	pPlayer->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
	pPlayer->EndHit();

	//pPlayer->GetAnimator()->SetAnimOpt(EANIM_OPT::NORMAL);
}

void CPlayerHitState::HitSound()
{
	LARGE_INTEGER llCount;
	QueryPerformanceCounter(&llCount);
	srand((UINT)llCount.QuadPart);
	int iRand = rand();

	iRand = rand() % 3;

	CSound* pSound = nullptr;

	switch (iRand)
	{
	case 0:
		pSound = CResMgr::GetInst()->FindSound(L"DAM_S");
		break;
	case 1:
		pSound = CResMgr::GetInst()->FindSound(L"DAM_S_02");
		break;
	case 2:
		pSound = CResMgr::GetInst()->FindSound(L"DAM_S_03");
		break;
	}

	pSound->Play();
}