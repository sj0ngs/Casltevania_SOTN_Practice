#include "pch.h"
#include "CBloodSkeleton.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CTimeMgr.h"

#include "CAI.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidBody.h"

#include "CPatrolState.h"

#include "CSound.h"

CBloodSkeleton::CBloodSkeleton() :
	m_bCollapse(false),
	m_faccCollapseTime(0.f),
	m_faccReviveTime(0.f)
{
	GetCollider()->SetScale(Vec2(50.f, 180.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -90.f));

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Blood_Skeleton\\BLOOD_SKELETON_WALK_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Blood_Skeleton\\BLOOD_SKELETON_WALK_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Blood_Skeleton\\BLOOD_SKELETON_COLLAPSE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Blood_Skeleton\\BLOOD_SKELETON_COLLAPSE_RIGHT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Blood_Skeleton\\BLOOD_SKELETON_RISE_LEFT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Blood_Skeleton\\BLOOD_SKELETON_RISE_RIGHT.anim");

	GetAI()->AddState(L"Patrol", new CPatrolState);
	GetAI()->ChangeState(L"Patrol");
}

CBloodSkeleton::~CBloodSkeleton()
{
}

void CBloodSkeleton::Tick()
{
	CMonster::Tick();

	if (m_bCollapse)
	{
		m_faccCollapseTime += DELTATIME;

		if (5.f <= m_faccCollapseTime)
		{
			Revive();
		}
	}
}

void CBloodSkeleton::Render(HDC _DC)
{
	CMonster::Render(_DC);
}

void CBloodSkeleton::Walk()
{
	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Blood_Skeleton_Walk_Right", true);
	}
	else
	{
		GetAnimator()->Play(L"Blood_Skeleton_Walk_Left", true);
	}
}

void CBloodSkeleton::Turn()
{
	CMonster::Turn();

	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Blood_Skeleton_Walk_Right", true);
	}
	else
	{
		GetAnimator()->Play(L"Blood_Skeleton_Walk_Left", true);
	}
}

void CBloodSkeleton::Dead()
{
	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Blood_Skeleton_Collapse_Right", false);
	}
	else
	{
		GetAnimator()->Play(L"Blood_Skeleton_Collapse_Left", false);
	}

	GetCollider()->SetScale(Vec2(0.f, 0.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, 1.f));
	GetRigidBody()->SetGravity(false);
	m_bCollapse = true;

	PLAY_SOUND(L"Skeleton_Die");
}

void CBloodSkeleton::Revive()
{
	if (GetFaceDir())
	{
		GetAnimator()->Play(L"Blood_Skeleton_Rise_Right", false);
	}
	else
	{
		GetAnimator()->Play(L"Blood_Skeleton_Rise_Left", false);
	}

	m_faccReviveTime += DELTATIME;

	if (0.8 <= m_faccReviveTime)
	{
		GetMonsterInfo().m_iHP = GetMonsterInfo().m_iMaxHP;
		GetCollider()->SetScale(Vec2(50.f, 180.f));
		GetCollider()->SetOffsetPos(Vec2(0.f, -90.f));
		GetRigidBody()->SetGravity(true);
		GetAI()->ChangeState(L"Patrol");
		m_faccCollapseTime = 0.f;
		m_faccReviveTime = 0.f;
		m_bCollapse = false;
	}
}
