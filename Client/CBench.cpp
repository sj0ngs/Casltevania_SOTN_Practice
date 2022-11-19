#include "pch.h"
#include "CBench.h"

#include "CObjMgr.h"
#include "CLevelMgr.h"
#include "CResMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CPlayer.h"
#include "CEffect.h"
#include "CLevel.h"

#include "CSound.h"

bool CBench::m_bBroken = false;

CBench::CBench()
{
	CreateCollider();
	CreateAnimator();

	GetCollider()->SetScale(Vec2(96.f, 188.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -94.f));

	GetAnimator()->LoadAnimation(L"animation\\MapObj\\BENCH.anim");
	GetAnimator()->LoadAnimation(L"animation\\MapObj\\BENCH_BREAK.anim");
}

CBench::CBench(const CBench& _pOther)	:
	CObj(_pOther)
{

	if (m_bBroken)
	{
		GetCollider()->SetScale(Vec2(0.f, 0.f));
		GetAnimator()->Play(L"Bench_Break", false);
		GetAnimator()->GetCurAnimation()->SetCurFrame(11);
	}
	else
	{
		GetAnimator()->Play(L"Bench", true);
	}
}

CBench::~CBench()
{
}

void CBench::BeginOverlap(CCollider* _pOther)
{
	if (!m_bBroken)
	{
		CObj* pOwner = _pOther->GetOwner();

		if (ELAYER::PLAYER_PROJECTILE == pOwner->GetLayer())
		{
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->GetLayer(ELAYER::PLAYER)[0]);
			assert(pPlayer);
			pPlayer->LifeMaxUp();

			GetCollider()->SetScale(Vec2(0.f, 0.f));
			GetAnimator()->Play(L"Bench_Break", false);

			CSound* pSound = CResMgr::GetInst()->FindSound(L"CANDLE");
			pSound->Play(false);

			m_bBroken = true;
		}
	}
}
