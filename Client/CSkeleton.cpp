#include "pch.h"
#include "CSkeleton.h"

#include "CLevelMgr.h"

#include "CLevel.h";

#include "CEffect.h"
#include "CPlayer.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAI.h"

#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttackState.h"
#include "CDeadState.h"
#include "CDeadState.h"

#include "CBone.h"

CSkeleton::CSkeleton()	:
	m_bThrowEnd(false)
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

		if (!m_bThrowEnd && 5 == GetAnimator()->GetCurAnimation()->GetCurFrame())
		{
			Throw();
			m_bThrowEnd = true;
		}

		if (GetMonsterInfo().m_fAttackTime <= m_faccAttackTime)
		{
			SetOnAttack(false);
			m_faccAttackTime = 0.f;	
			m_bThrowEnd = false;
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

	pEffect->GetAnimator()->Play(false);

	Instantiate(pEffect, GetPos(), ELAYER::EFFECT);
	SetDead();
}

void CSkeleton::Throw()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->GetLayer(ELAYER::PLAYER)[0]);
	assert(pPlayer);

	Vec2 vDir = GetPos() - pPlayer->GetPos();
	Vec2 vPos = GetPos(); 

	CBone* pBone = new CBone;
	int iDmg = GetMonsterInfo().m_iAtk;
	pBone->SetDamage(iDmg);
	pBone->SetFaceDir(GetFaceDir());
	if (GetFaceDir())
	{
		vPos.x += 0.f;
		vPos.y -= 150.f;
		pBone->GetRigidBody()->AddVelocity(Vec2(vDir.Length() * 1.f, -1000.f));
		pBone->GetAnimator()->Play(L"Skeleton_Bone_Right", true);
	}
	else
	{
		vPos.x -= 0.f;
		vPos.y -= 150.f;
		pBone->GetRigidBody()->AddVelocity(Vec2(vDir.Length() * -1.f, -1000.f));
		pBone->GetAnimator()->Play(L"Skeleton_Bone_Left", true);
	}

	Instantiate(pBone, vPos, ELAYER::MONSTER_PROJECTILE);
}
