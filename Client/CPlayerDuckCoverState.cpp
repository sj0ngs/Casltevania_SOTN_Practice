#include "pch.h"
#include "CPlayerDuckCoverState.h"

#include "CPlayer.h"

CPlayerDuckCoverState::CPlayerDuckCoverState()
{
}

CPlayerDuckCoverState::~CPlayerDuckCoverState()
{
}

void CPlayerDuckCoverState::Final_Tick()
{
	if (IS_RELEASED(EKEY::S))
	{
		if (IS_PRESSED(EKEY::DOWN))
			ChangeState(L"Duck");
		else
			ChangeState(L"GetUp");
	}
}

void CPlayerDuckCoverState::Enter()
{
	GET_PLAYER();

	CCover* pCover = new CCover();
	Vec2 vOffsetPos = {};
	Vec2 vScale = {};

	Vec2 vObjPos = pPlayer->GetPos();
	Vec2 vObjScale = pPlayer->GetCollider()->GetScale();

	vScale = Vec2(30.f, 100.f);
	// ������ �ٶ�
	if (pPlayer->GetFaceDir())
	{
		SET_ANIM(L"Duck_Cover_Right");
		vOffsetPos = Vec2(vObjScale.x / 2.f + vScale.x / 2.f, -60.f);
	}
	// ���� �ٶ�
	else
	{
		SET_ANIM(L"Duck_Cover_Left");
		vOffsetPos = Vec2(-(vObjScale.x / 2.f + vScale.x / 2.f), -60.f);
	}

	pCover->GetCollider()->SetScale(vScale);
	pCover->GetCollider()->SetOffsetPos(vOffsetPos);
	Instantiate(pCover, vObjPos, ELAYER::PLAYER_PROJECTILE);
	SetCover(pCover);
}
