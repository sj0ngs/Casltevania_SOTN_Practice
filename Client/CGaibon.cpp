#include "pch.h"
#include "CGaibon.h"

#include "CGaibonMoveState.h"
#include "CGaibonSkyAttack.h"

CGaibon::CGaibon()	:
	m_eState(EGAIBON_STATE::PHASE_1)
{
	GetCollider()->SetScale(Vec2(70.f, 220.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -100.f));

	GetRigidBody()->SetFriction(1000.f);
	GetRigidBody()->SetGravity(false);
	GetRigidBody()->SetGravityAccel(1500.f);
	GetRigidBody()->SetVelocityLimit(1000.f);

	// Phase 1
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_IDLE_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_ATTACK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_LANDING_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_LANDING_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_LAND_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_LAND_ATTACK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_CHANGE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_CHANGE_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_PICK_UP_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_PICK_UP_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_DEATH_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_DEATH_RIGHT.anim");

	// Phase 2
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_SKY_IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_SKY_IDLE_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_SKY_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_SKY_ATTACK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_LANDING_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_LANDING_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_LAND_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_LAND_ATTACK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_SKY_PICK_UP_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_SKY_PICK_UP_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_DEATH_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_P2_DEATH_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_DEATH_EFFECT_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_DEATH_EFFECT_RIGHT.anim");

	GetAI()->AddState(L"GaibonMove", new CGaibonMoveState);
	GetAI()->AddState(L"GaibonSkyAttack", new CGaibonSkyAttack);
	//GetAI()->ChangeState(L"GaibonMove");
}

CGaibon::~CGaibon()
{
}

void CGaibon::Tick()
{
	CObj::Tick();

	if (nullptr == GetAI()->GetCurState())
	{
		GetAI()->ChangeState(L"GaibonMove");
	}
}

void CGaibon::Render(HDC _DC)
{
	CMonster::Render(_DC);
}

void CGaibon::BeginOverlap(CCollider* _pOther)
{
}

void CGaibon::Walk()
{
	GetRigidBody()->SetGravity(false);

	switch (m_eState)
	{
	case EGAIBON_STATE::PHASE_1:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_Sky_Idle_Right", true);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_Sky_Idle_Left", true);
		}
		break;
	case EGAIBON_STATE::PHASE_2:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_P2_Sky_Idle_Right", true);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_P2_Sky_Idle_Left", true);
		}
		break;
	}
}

void CGaibon::Turn()
{
	CMonster::Turn();

	Walk();
}

void CGaibon::SkyAttack()
{
	switch (m_eState)
	{
	case EGAIBON_STATE::PHASE_1:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_Sky_Attack_Right", true);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_Sky_Attack_Left", true);
		}
		break;
	case EGAIBON_STATE::PHASE_2:
		if (GetFaceDir())
		{
			GetAnimator()->Play(L"Gaibon_P2_Sky_Attack_Right", true);
		}
		else
		{
			GetAnimator()->Play(L"Gaibon_P2_Sky_Attack_Left", true);
		}
		break;
	}
}

void CGaibon::Dead()
{
}
