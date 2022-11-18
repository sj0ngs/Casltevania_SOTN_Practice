#include "pch.h"
#include "CPlayerSkillState.h"

#include "CResMgr.h"
#include "CPlayer.h"

#include "CSound.h"

#include "CEffect.h"

CPlayerSkillState::CPlayerSkillState() :
	m_bSkillEnd(false)
{
}

CPlayerSkillState::~CPlayerSkillState()
{
}

void CPlayerSkillState::Final_Tick()
{
	GET_PLAYER();

	switch (pPlayer->GetPlayerSkill())
	{
	case EPLAYER_SKILL::ITEM_CRASH:
	{
		if (!pPlayer->IsOnCrash())
		{
			ChangeState(L"Idle");
		}
	}
		break;
	case EPLAYER_SKILL::HELL_FIRE:
	{
		if (!m_bSkillEnd && 7 == GetAnim()->GetCurFrame())
		{
			pPlayer->HellFire();
			m_bSkillEnd = true;
		}

		if (GetAnim()->IsFinish())
			ChangeState(L"Idle");
	}
	break;
	case EPLAYER_SKILL::NONE:
		assert(false);
		break;
	}
}

void CPlayerSkillState::Enter()
{
	GET_PLAYER();

	switch (pPlayer->GetPlayerSkill())
	{
	case EPLAYER_SKILL::ITEM_CRASH:
	{
		if (!pPlayer->ItemCrash())
		{
			ChangeState(L"Idle");
			return;
		}

		if (pPlayer->GetFaceDir())
		{
			SET_ANIM(L"Item_Crash_Right");
		}
		// ¿ÞÂÊ ¹Ù¶óº½
		else
		{
			SET_ANIM(L"Item_Crash_Left");
		}
	}
		break;
	case EPLAYER_SKILL::HELL_FIRE:
	{
		if (pPlayer->GetFaceDir())
		{
			SET_ANIM(L"HellFire_Right");
		}
		// ¿ÞÂÊ ¹Ù¶óº½
		else
		{
			SET_ANIM(L"HellFire_Left");
		}
	}
		break;
	case EPLAYER_SKILL::NONE:
		assert(false);
		break;
	}

	LARGE_INTEGER llCount;
	QueryPerformanceCounter(&llCount);
	srand((UINT)llCount.QuadPart);
	int iRand = rand();

	iRand = rand() % 3;

	CSound* pSound = nullptr;

	switch (iRand)
	{
	case 0:
		pSound = CResMgr::GetInst()->FindSound(L"SKILL_1");
		break;
	case 1:
		pSound = CResMgr::GetInst()->FindSound(L"SKILL_2");
		break;
	case 2:
		pSound = CResMgr::GetInst()->FindSound(L"SKILL_3");
		break;
	}

	pSound->Play();

	Vec2 vPos = CCamera::GetInst()->GetRealPos(Vec2(0.f, 360.f));
	vPos.x = pPlayer->GetPos().x;

	CEffect* pEffect = new CEffect;
	pEffect->GetAnimator()->LoadAnimation(L"animation\\Effect\\LIGHT.anim");
	pEffect->GetAnimator()->Play(false);
	Instantiate(pEffect, vPos, ELAYER::EFFECT);
}

void CPlayerSkillState::Exit()
{
	GET_PLAYER();

	pPlayer->SetPlayerSkill(EPLAYER_SKILL::NONE);
	CPlayerState::Exit();

	m_bSkillEnd = false;
}
