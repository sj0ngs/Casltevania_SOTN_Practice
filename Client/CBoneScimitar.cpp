#include "pch.h"
#include "CBoneScimitar.h"

#include "CEffect.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAI.h"

#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttackState.h"
#include "CDeadState.h"
#include "CDeadState.h"

#include "CMonsterAttack.h"

CBoneScimitar::CBoneScimitar()	:
	m_bAttackEnd(false)
{
	GetCollider()->SetScale(Vec2(50.f, 160.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -80.f));

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Bone_Scimitar\\BONE_SCIMITAR_IDLE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Bone_Scimitar\\BONE_SCIMITAR_IDLE_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Bone_Scimitar\\BONE_SCIMITAR_WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Bone_Scimitar\\BONE_SCIMITAR_WALK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Bone_Scimitar\\BONE_SCIMITAR_ATTACK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Bone_Scimitar\\BONE_SCIMITAR_ATTACK_RIGHT.anim");

	GetAI()->AddState(L"Idle", new CIdleState);
	GetAI()->AddState(L"Trace", new CTraceState);
	GetAI()->AddState(L"Attack", new CAttackState);
	GetAI()->ChangeState(L"Idle");
}

CBoneScimitar::~CBoneScimitar()
{
}

void CBoneScimitar::Tick()
{
	CMonster::Tick();

	if (IsAttack())
	{
		m_faccAttackTime += DELTATIME;

		if (!m_bAttackEnd && 2 == GetAnimator()->GetCurAnimation()->GetCurFrame())
		{
			Slash();
			m_bAttackEnd = true;
		}

		if (GetMonsterInfo().m_fAttackTime <= m_faccAttackTime)
		{
			SetOnAttack(false);
			m_faccAttackTime = 0.f;
			m_bAttackEnd = false;
		}
	}
}

void CBoneScimitar::Render(HDC _DC)
{
	CMonster::Render(_DC);
}

void CBoneScimitar::Idle()
{
	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Bone_Scimitar_Idle_Right", true);
	}
	else
	{
		GetAnimator()->Play(L"Bone_Scimitar_Idle_Left", true);
	}
}

void CBoneScimitar::Walk()
{
	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Bone_Scimitar_Walk_Right", true);
	}
	else
	{
		GetAnimator()->Play(L"Bone_Scimitar_Walk_Left", true);
	}
}

void CBoneScimitar::Turn()
{
	CMonster::Turn();

	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Bone_Scimitar_Walk_Right", true);
	}
	else
	{
		GetAnimator()->Play(L"Bone_Scimitar_Walk_Left", true);
	}
}


void CBoneScimitar::Attack()
{
	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Bone_Scimitar_Attack_Right", false);
	}
	else
	{
		GetAnimator()->Play(L"Bone_Scimitar_Attack_Left", false);
	}

	SetOnAttack(true);
}

void CBoneScimitar::Dead()
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

	pEffect->GetAnimator()->Play(false);

	Instantiate(pEffect, GetPos(), ELAYER::EFFECT);
	SetDead();
}

void CBoneScimitar::Slash()
{
	CMonsterAttack* pAttack = new CMonsterAttack;

	pAttack->SetDamage(GetMonsterInfo().m_iAtk);
	pAttack->SetLifeSpan(0.5f);
	pAttack->GetCollider()->SetScale(Vec2(120.f, 25.f));

	Vec2 vPos = {};
	vPos.y -= 80.f;

	if (GetFaceDir())
	{
		vPos.x += (25.f + 60.f);
	}
	else
	{
		vPos.x -= (25.f + 60.f);
	}

	pAttack->GetCollider()->SetOffsetPos(vPos);

	Instantiate(pAttack, GetPos(), ELAYER::MONSTER_PROJECTILE);
}
