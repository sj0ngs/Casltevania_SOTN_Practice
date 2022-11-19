#include "pch.h"
#include "CCandle.h"

#include "CObjMgr.h"
#include "CResMgr.h"

#include "CCollider.h"
#include "CAnimator.h"

#include "CEffect.h"

#include "CHeart.h"

#include "CSubWeapon.h"

#include "CSound.h"

CCandle::CCandle()
{
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetScale(Vec2(50.f, 80.f));
	GetAnimator()->LoadAnimation(L"animation\\MapObj\\CANDLE.anim");
	GetAnimator()->LoadAnimation(L"animation\\MapObj\\CANDLE_2.anim");

	//GetAnimator()->Play(true);
}

CCandle::~CCandle()
{
}

void CCandle::BeginOverlap(CCollider* _pOther)
{
	SetDead();

	CEffect* pEffect = ((CEffect*)CObjMgr::GetInst()->FindObj(L"Burn_Effect_3"))->Clone();
	Instantiate(pEffect, GetPos(), ELAYER::EFFECT);

	DropItem();

	CSound* pSound = CResMgr::GetInst()->FindSound(L"Projectile_Explot");
	pSound->Play();
}

void CCandle::DropItem()
{
	LARGE_INTEGER llCount;
	QueryPerformanceCounter(&llCount);
	srand((UINT)llCount.QuadPart);

	int iRand = rand();
	iRand = rand() % 100 + 1;

	if (80 >= iRand)
	{
		DropHeart();
	}
	else
	{
		DropSubWeapon();
	}
}

void CCandle::DropHeart()
{
	LARGE_INTEGER llCount;
	QueryPerformanceCounter(&llCount);
	srand((UINT)llCount.QuadPart);

	int iRand = rand();
	iRand = rand() % 100 + 1;

	CHeart* pHeart = nullptr;
	if (20 > iRand)
	{
		pHeart = ((CHeart*)CObjMgr::GetInst()->FindObj(L"Large_Heart"))->Clone();
	}
	else if(60 > iRand)
	{
		pHeart = ((CHeart*)CObjMgr::GetInst()->FindObj(L"Small_Heart"))->Clone();
	}
	else
	{
		pHeart = ((CHeart*)CObjMgr::GetInst()->FindObj(L"HP_Heart"))->Clone();
	}

	Instantiate(pHeart, GetPos(), ELAYER::ITEM);
}

void CCandle::DropSubWeapon()
{
	LARGE_INTEGER llCount;
	QueryPerformanceCounter(&llCount);
	srand((UINT)llCount.QuadPart);

	int iRand = rand();
	iRand = rand() % 3 + 1;

	CSubWeapon* pSubWeapon = (CSubWeapon*)CObjMgr::GetInst()->FindObj(L"Drop_SubWeapon")->Clone();
	if (1 == iRand)
	{
		pSubWeapon->SetSubWeaponType(ESUB_WEAPON_TYPE::DAGGER);
	}
	else if (2 == iRand)
	{
		pSubWeapon->SetSubWeaponType(ESUB_WEAPON_TYPE::AXE);
	}
	else if(3 == iRand)
	{
		pSubWeapon->SetSubWeaponType(ESUB_WEAPON_TYPE::BIBLE);
	}

	Instantiate(pSubWeapon, GetPos(), ELAYER::ITEM);
}
