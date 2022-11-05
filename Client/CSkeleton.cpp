#include "pch.h"
#include "CSkeleton.h"

#include "CEffect.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAI.h"

#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttackState.h"
#include "CDeadState.h"
#include "CDeadState.h"

#include "CBone.h"

CSkeleton::CSkeleton()
{
	GetCollider()->SetScale(Vec2(50.f, 160.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -80.f));

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Skeleton\\SKELETON_IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Skeleton\\SKELETON_IDLE_RIGHT.anim");
													   
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Skeleton\\SKELETON_WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Skeleton\\SKELETON_WALK_RIGHT.anim");
													   
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Skeleton\\SKELETON_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Skeleton\\SKELETON_ATTACK_RIGHT.anim");
													   
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Skeleton\\SKELETON_DEATH_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Skeleton\\SKELETON_DEATH_RIGHT.anim");

	GetAI()->AddState(L"Idle", new CIdleState);
	GetAI()->AddState(L"Trace", new CTraceState);
	GetAI()->AddState(L"Attack", new CAttackState);
	GetAI()->ChangeState(L"Idle");
}

CSkeleton::~CSkeleton()
{
}

void CSkeleton::Tick()
{
	CMonster::Tick();

	if (IsAttack())
	{
		m_faccAttackTime += DELTATIME;

		if (GetMonsterInfo().m_fAttackTime <= m_faccAttackTime)
		{
			Vec2 vPos = GetPos();

			SetOnAttack(false);
			m_faccAttackTime = 0.f;
		}
	}
}

void CSkeleton::Render(HDC _DC)
{
	CMonster::Render(_DC);
}

void CSkeleton::Idle()
{
	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Skeleton_Idle_Right", true);
	}
	else
	{
		GetAnimator()->Play(L"Skeleton_Idle_Left", true);
	}
}

void CSkeleton::Walk()
{
	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Skeleton_Walk_Right", true);
	}
	else
	{
		GetAnimator()->Play(L"Skeleton_Walk_Left", true);
	}
}

void CSkeleton::Turn()
{
	CMonster::Turn();

	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Skeleton_Walk_Right", true);
	}
	else
	{
		GetAnimator()->Play(L"Skeleton_Walk_Left", true);
	}
}

void CSkeleton::Attack()
{
	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Skeleton_Attack_Right", false);
	}
	else
	{
		GetAnimator()->Play(L"Skeleton_Attack_Left", false);
	}

	SetOnAttack(true);
}

void CSkeleton::Dead()
{
	CEffect* pEffect = new CEffect;

	if (GetFaceDir())
	{
		pEffect->GetAnimator()->LoadAnimation(L"animation\\Monster\\Skeleton\\SKELETON_DEATH_RIGHT.anim");
	}
	else
	{
		pEffect->GetAnimator()->LoadAnimation(L"animation\\Monster\\Skeleton\\SKELETON_DEATH_LEFT.anim");
	}

	pEffect->GetAnimator()->Play();

	Instantiate(pEffect, GetPos(), ELAYER::EFFECT);
	SetDead();
}
