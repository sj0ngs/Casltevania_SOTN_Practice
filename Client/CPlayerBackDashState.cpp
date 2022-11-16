#include "pch.h"
#include "CPlayerBackDashState.h"

#include "CResMgr.h"
#include "CPlayer.h"
#include "CSound.h"

#include "CEffect.h"

CPlayerBackDashState::CPlayerBackDashState()	:
	m_faccDashTime(0.f),
	m_fDashSpeed(400.f),
	m_bEffect(false)
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
		{
			Attack(L"StandAttack");
			return;
		}
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

		if (!m_bEffect && 12 == GetAnim()->GetCurFrame())
		{
			Vec2 vPos = pPlayer->GetPos();

			if (pPlayer->GetFaceDir())
			{
				vPos.x -= 30.f;
			}
			else
			{
				vPos.x += 30.f;
			}

			vPos.y -= 25.f;

			CEffect* pEffect = new CEffect;

			pEffect->GetAnimator()->LoadAnimation(L"animation\\Effect\\DUST.anim");
			pEffect->GetAnimator()->Play(false);

			Instantiate(pEffect, vPos, ELAYER::FRONT_EFFECT);

			m_bEffect = true;
		}
	}
	else
	{
		ChangeState(L"Idle");
		return;
	}

	CPlayerState::Final_Tick();
	//Hit();
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

	pPlayer->SetOnTrail(true);

	PLAY_SOUND(L"SLIDE");
}

void CPlayerBackDashState::Exit()
{
	GET_PLAYER();
	pPlayer->SetOnTrail(false);

	CPlayerState::Exit();
	m_faccDashTime = 0.f;

	m_bEffect = false;
}
