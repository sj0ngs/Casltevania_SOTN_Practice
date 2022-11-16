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
		ChangeState(L"GetUp");
	else if (IS_TAP(EKEY::A))
		Attack(L"DuckAttack");
	else if (IS_TAP(EKEY::S))
		ChangeState(L"DuckCover");
	else if(IS_PRESSED(EKEY::DOWN))
	{
		if (IS_TAP(EKEY::SPACE) && pPlayer->CanGoDown())
		{
			ChangeState(L"Fall");
			pPlayer->SetGoDown(false);
			pPlayer->GetUp();
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
		

	CPlayerState::Final_Tick();
	//Hit();
}

void CPlayerDuckState::Enter()
{
	GET_PLAYER();

	if (pPlayer->IsDuck())
	{
		if (pPlayer->GetFaceDir())
			pPlayer->GetAnimator()->Shift(L"Duck_Right", false, 7);
		else
			pPlayer->GetAnimator()->Shift(L"Duck_Left", false, 7);
	}
	else
	{
		if (pPlayer->GetFaceDir())
			pPlayer->GetAnimator()->Play(L"Duck_Right", false);
		else
			pPlayer->GetAnimator()->Play(L"Duck_Left", false);
	}

	pPlayer->Duck();

	pPlayer->SetOnTrail(true);
}

void CPlayerDuckState::Exit()
{
	GET_PLAYER();

	pPlayer->SetOnTrail(false);
	CPlayerState::Exit();
}
