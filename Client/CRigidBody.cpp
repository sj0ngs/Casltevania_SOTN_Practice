#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"

#include "CObj.h"
#include "CPlayer.h"

CRigidBody::CRigidBody(CObj* _pOwner) :
	CComponent(_pOwner),
	m_vForce{},
	m_vVelocity{},
	m_fMass(1.f),
	m_fFriction(300.f),
	m_fFrictionScale(1.f),
	m_fVelocityLimit(10000.f),
	m_fGravityVLimit(10000.f),
	m_fGravityAccel(100.f),
	m_bGravityUse(false),
	m_iGround(0)
{
}

CRigidBody::CRigidBody(const CRigidBody& _Other)	:
	CComponent(nullptr),
	m_vForce{},
	m_vVelocity{},
	m_fMass(_Other.m_fMass),
	m_fFriction(_Other.m_fFriction),
	m_fFrictionScale(_Other.m_fFrictionScale),
	m_fVelocityLimit(_Other.m_fVelocityLimit),
	m_fGravityVLimit(_Other.m_fGravityVLimit),
	m_fGravityAccel(_Other.m_fGravityAccel),
	m_bGravityUse(_Other.m_bGravityUse),
	m_iGround(0)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Tick()
{
}

void CRigidBody::Final_Tick()
{
	// f = ma 
	Vec2 vAccel = m_vForce / m_fMass;

	m_vVelocity += vAccel * DELTATIME;

	if (m_bGravityUse && (0 < m_iGround) || !m_bGravityUse)
	{
		// 마찰 가속도
		Vec2 vFriction = -m_vVelocity;

		if (!vFriction.IsZero())
		{
			vFriction.Normalize();
			vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DELTATIME);
		}

		// 현재 속도보다 감소량이 작을경우에는 속도를 0으로 만든다
		if (m_vVelocity.Length() <= vFriction.Length())
			m_vVelocity = Vec2(0.f, 0.f);
		else
			m_vVelocity += vFriction;
	}

	// 중력 적용 + 공중 상태 --> 중력
	if (m_bGravityUse && !(0 < m_iGround))
	{
		Vec2 vGravityAccel = Vec2(0.f, m_fGravityAccel);
		m_vVelocity += vGravityAccel * DELTATIME;
	}

	// 속도 제한 설정(좌, 우)
	// 중력을 사용하는 경우, 좌우 이동과 중력방향에 제한 속도를 따로 설정한다
	if (m_bGravityUse)
	{
		if (m_fVelocityLimit < fabsf(m_vVelocity.x))
		{
			m_vVelocity.x =  m_vVelocity.x / fabsf(m_vVelocity.x) * m_fVelocityLimit;
		}

		if (m_fGravityVLimit < fabsf(m_vVelocity.y))
		{
			m_vVelocity.y = m_vVelocity.y / fabsf(m_vVelocity.y) * m_fGravityVLimit;
		}
	}
	// 중력의 영향을 안 받으면 어느 방향으로든 속도에 제한을 건다
	else
	{
		if (m_fVelocityLimit < m_vVelocity.Length())
		{
			m_vVelocity.Normalize();
			m_vVelocity *= m_fVelocityLimit;
		}
	}

	// 오브젝트의 위치
	Vec2 vPos = GetOwner()->GetPos();

	vPos.x += m_vVelocity.x * DELTATIME;
	vPos.y += m_vVelocity.y * DELTATIME;

	GetOwner()->SetPos(vPos);

	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Render(HDC _hDC)
{
}

