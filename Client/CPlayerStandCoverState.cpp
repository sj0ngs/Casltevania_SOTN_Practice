#include "pch.h"
#include "CPlayerStandCoverState.h"

#include "CPlayer.h"

CPlayerStandCoverState::CPlayerStandCoverState()
{
}

CPlayerStandCoverState::~CPlayerStandCoverState()
{
}

void CPlayerStandCoverState::Final_Tick()
{
	if (IS_RELEASED(EKEY::S))
		ChangeState(L"Idle");
}

void CPlayerStandCoverState::Enter()
{
	GET_PLAYER();

	CCover* pCover = new CCover();
	SetCover(pCover);
	Vec2 vOffsetPos = {};
	Vec2 vScale = {};

	Vec2 vObjPos = pPlayer->GetPos();
	Vec2 vObjScale = pPlayer->GetCollider()->GetScale();

	vScale = Vec2(40.f, 100.f);
	// ¿À¸¥ÂÊ ¹Ù¶óº½
	if (pPlayer->GetFaceDir())
	{
		SET_ANIM(L"Stand_Cover_Right");
		vOffsetPos = Vec2(vObjScale.x / 2.f + vScale.x / 2.f, -130.f);
	}
	// ¿ÞÂÊ ¹Ù¶óº½
	else
	{
		SET_ANIM(L"Stand_Cover_Left");
		vOffsetPos = Vec2(-(vObjScale.x / 2.f + vScale.x / 2.f), -130.f);
	}

	pCover->GetCollider()->SetScale(vScale);
	pCover->GetCollider()->SetOffsetPos(vOffsetPos);
	Instantiate(pCover, vObjPos, ELAYER::PLAYER_PROJECTILE);
}
