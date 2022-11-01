#include "pch.h"
#include "CPlayerBackDashState.h"

#include "CPlayer.h"

CPlayerBackDashState::CPlayerBackDashState()	:
	m_faccDashTime(0.f),
	m_fDashSpeed(400.f)
{
}

CPlayerBackDashState::~CPlayerBackDashState()
{
}

void CPlayerBackDashState::Final_Tick()
{
	GET_PLAYER();

	if (!GetAnim()->IsFinish())
	{
		if (IS_TAP(EKEY::A))
			Attack(L"StandAttack");
		if (0.5f <= m_faccDashTime)
		{
			if (IS_PRESSED(EKEY::LEFT))
			{
				ChangeState(L"Move_Left");
				return;
			}

			if (IS_PRESSED(EKEY::RIGHT))
			{
				ChangeState(L"Move_Right");
				return;
			}
		}
		else
		{
			Vec2 vPos = pPlayer->GetPos();
			Vec2 vDir = pPlayer->GetDir();

			if (pPlayer->GetFaceDir())
				vPos -= vDir * m_fDashSpeed * DELTATIME;
			else
				vPos += vDir * m_fDashSpeed * DELTATIME;

			m_faccDashTime += DELTATIME;
			pPlayer->SetPos(vPos);
		}
	}
	else
		ChangeState(L"Idle");
}

void CPlayerBackDashState::Enter()
{
	GET_PLAYER();

	if (pPlayer->GetFaceDir())
	{
		SetAnim(pPlayer->GetAnimator()->FindAnimation(L"Walk_End_Right"));
		pPlayer->GetAnimator()->Play(L"Walk_End_Right", false);
	}
	else
	{
		SetAnim(pPlayer->GetAnimator()->FindAnimation(L"Walk_End_Left"));
		pPlayer->GetAnimator()->Play(L"Walk_End_Left", false);
	}
}

void CPlayerBackDashState::Exit()
{
	CPlayerState::Exit();
	m_faccDashTime = 0.f;
}
