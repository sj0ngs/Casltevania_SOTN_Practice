#include "pch.h"
#include "CHeart.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"

#include "CPlayer.h"

#include "CSound.h"

CHeart::CHeart()	:
	m_eType(EHEART_TYPE::NONE),
	m_iHealValue(0),
	m_faccMoveTime(0.f),
	m_iDir(1),
	m_fDegree(0.f)
{
	CreateCollider();
	CreateAnimator();
	CreateRigidBody();

	GetRigidBody()->SetGravity(true);

	GetAnimator()->LoadAnimation(L"animation\\Item\\SMALL_HEART.anim");
	GetAnimator()->LoadAnimation(L"animation\\Item\\LARGE_HEART.anim");
	GetAnimator()->LoadAnimation(L"animation\\Item\\HP_HEART.anim");
}

CHeart::~CHeart()
{
}

void CHeart::SetHeartType(EHEART_TYPE _eType)
{
	m_eType = _eType;

	switch (m_eType)
	{
	case EHEART_TYPE::SMALL_HEART:
	{
		GetAnimator()->Play(L"Small_Heart", true);
		GetCollider()->SetScale(Vec2(20.f, 20.f));
		GetRigidBody()->SetGravityAccel(50.f);
		GetRigidBody()->SetGravityVelocityLimit(50.f);
		m_iHealValue = 1;
	}
		break;
	case EHEART_TYPE::LARGE_HEART:
	{
		GetAnimator()->Play(L"Large_Heart", true);
		GetCollider()->SetScale(Vec2(40.f, 40.f));
		GetRigidBody()->SetGravityAccel(1000.f);
		m_iHealValue = 5;
	}
		break;
	case EHEART_TYPE::HP_HEART:
	{
		GetAnimator()->Play(L"HP_Heart", true);
		GetCollider()->SetScale(Vec2(30.f, 30.f));
		m_iHealValue = 5;
	}
		break;
	}
}

void CHeart::Tick()
{
	switch (m_eType)
	{
	case EHEART_TYPE::SMALL_HEART:
		SmallHeartMove();
		break;
	case EHEART_TYPE::LARGE_HEART:
		break;
	case EHEART_TYPE::HP_HEART:
		break;
	}

	CObj::Tick();
}

void CHeart::BeginOverlap(CCollider* _pOther)
{
	CObj* pObj = _pOther->GetOwner();

	if (ELAYER::PLAYER == pObj->GetLayer())
	{
		CPlayer* pPlayer = (CPlayer*)pObj;

		switch (m_eType)
		{
		case EHEART_TYPE::SMALL_HEART:
		case EHEART_TYPE::LARGE_HEART:
			pPlayer->AddHeart(m_iHealValue);
			break;
		case EHEART_TYPE::HP_HEART:
			pPlayer->TakeDamage(-1 * m_iHealValue, true);
			break;
		case EHEART_TYPE::NONE:
			break;
		}

		SetDead();

		PLAY_SOUND(L"GETHEART");
	}
}

void CHeart::SmallHeartMove()
{
	if (!GetRigidBody()->IsGround())
	{
		if (SMALL_HEART_MOVE / 2.f > m_faccMoveTime)
		{
			GetRigidBody()->AddForce(Vec2(m_iDir * 300.f, 0.f));
		}
		else
		{
			GetRigidBody()->AddForce(Vec2(m_iDir * 300.f * -1.f, 0.f));
		}

		if (SMALL_HEART_MOVE <= m_faccMoveTime)
		{
			Vec2 vVelocity = GetRigidBody()->GetVelocity();
			vVelocity.x = 0.f;
			GetRigidBody()->SetVelocity(vVelocity);
			m_iDir *= -1;
			m_faccMoveTime = 0.f;
		}

		m_faccMoveTime += DELTATIME;
	}
}
