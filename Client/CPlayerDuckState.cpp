#include "pch.h"
#include "CPlayerDuckState.h"

#include "CPlayer.h"

CPlayerDuckState::CPlayerDuckState()
{
}

CPlayerDuckState::~CPlayerDuckState()
{
}

void CPlayerDuckState::Final_Tick()
{
	GET_PLAYER();

	if (IS_RELEASED(EKEY::DOWN))
	{
		if (pPlayer->GetFaceDir())
		{
			SET_ANIM(L"Get_Up_Right");
		}
		else
		{
			SET_ANIM(L"Get_Up_Left");
		}
	}
	else if(IS_PRESSED(EKEY::DOWN))
	{
		if (IS_TAP(EKEY::SPACE) && pPlayer->CanGoDown())
		{
			ChangeState(L"Fall");
			pPlayer->SetGoDown(false);
			return;
		}

		if (IS_TAP(EKEY::RIGHT))
		{
			pPlayer->SetFaceDir(true);
			pPlayer->GetAnimator()->Shift(L"Duck_Right", false, 7);
		}
		else if (IS_TAP(EKEY::LEFT))
		{
			pPlayer->SetFaceDir(false);
			pPlayer->GetAnimator()->Shift(L"Duck_Left", false, 7);
		}
	}

	if (nullptr != GetAnim())
	{
		if (GetAnim()->IsFinish())
			ChangeState(L"Idle");
	}
}

void CPlayerDuckState::Enter()
{
	GET_PLAYER();

	if (pPlayer->GetFaceDir())
		pPlayer->GetAnimator()->Play(L"Duck_Right", false);
	else
		pPlayer->GetAnimator()->Play(L"Duck_Left", false);

	Vec2 vScale = pPlayer->GetCollider()->GetScale();
	vScale.y -= 90.f;
	pPlayer->GetCollider()->SetScale(vScale);
	pPlayer->GetCollider()->SetOffsetPos(Vec2(0.f, -45.f));
}

void CPlayerDuckState::Exit()
{
	CPlayerState::Exit();

	GET_PLAYER();

	Vec2 vScale = pPlayer->GetCollider()->GetScale();
	vScale.y += 90.f;
	pPlayer->GetCollider()->SetScale(vScale);
	pPlayer->GetCollider()->SetOffsetPos(Vec2(0.f, -90.f));
}
