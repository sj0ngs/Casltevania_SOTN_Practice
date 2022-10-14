#include "pch.h"
#include "CObj.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"

#include "CComponent.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CLineCollider.h"

// 오브젝트 dead 처리 함수
void CObj::SetDead()
{
	tEvent evn = {};
	evn.eType = EEVENT_TYPE::DELETE_OBJECT;
	evn.wParam = (DWORD_PTR)this;
	CEventMgr::GetInst()->AddEvent(evn);
}

CObj::CObj()	:
	m_vPos{},
	m_vScale{},
	m_pCollider(nullptr),
	m_pAnimator(nullptr),
	m_pRigidBody(nullptr),
	m_bDead(false)
{
}

CObj::CObj(const CObj& _Other)	:
	CEntity(_Other),
	m_vPos(_Other.m_vPos),
	m_vScale(_Other.m_vScale),
	m_pCollider(nullptr),
	m_pAnimator(nullptr),
	m_pRigidBody(nullptr),
	m_bDead(false)
{
	if (nullptr != _Other.m_pCollider)
	{
		m_pCollider = _Other.m_pCollider->Clone();
		m_pCollider->SetOwner(this);
	}

	if (nullptr != _Other.m_pAnimator)
	{
		m_pAnimator = _Other.m_pAnimator->Clone();
		m_pAnimator->SetOwner(this);
	}

	if (nullptr != _Other.m_pRigidBody)
	{
		m_pRigidBody = _Other.m_pRigidBody->Clone();
		m_pRigidBody->SetOwner(this);
	}
}

CObj::~CObj()
{
	DYNAMIC_DELETE(m_pCollider);
	DYNAMIC_DELETE(m_pAnimator);
	DYNAMIC_DELETE(m_pRigidBody);
}

void CObj::Tick()
{
	if (nullptr != m_pCollider)
		m_pCollider->Tick();

	if (nullptr != m_pAnimator)
		m_pAnimator->Tick();

	if (nullptr != m_pRigidBody)
		m_pRigidBody->Tick();
}

void CObj::Final_Tick()
{
	if (nullptr != m_pRigidBody)
		m_pRigidBody->Final_Tick();

	if (nullptr != m_pAnimator)
		m_pAnimator->Final_Tick();

	if (nullptr != m_pCollider)
		m_pCollider->Final_Tick();
}

void CObj::Render(HDC _DC)
{
	if (nullptr != m_pCollider)
		m_pCollider->Render(_DC);

	if (nullptr != m_pAnimator)
		m_pAnimator->Render(_DC);
}

void CObj::CreateCollider(ECOLLIDER_TYPE _eType)
{
	switch (_eType)
	{
	case ECOLLIDER_TYPE::BOX:
		m_pCollider = new CCollider(this);
		break;
	case ECOLLIDER_TYPE::LINE:
		m_pCollider = new CLineCollider(this);
		break;
	case ECOLLIDER_TYPE::PIXEL:
		break;
	case ECOLLIDER_TYPE::CIRCLE:
		break;
	default:
		break;
	}
}

void CObj::CreateAnimator()
{
	m_pAnimator = new CAnimator(this);
}

void CObj::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody(this);
}


void CObj::BeginOverlap(CCollider* _pOther)
{
}

void CObj::OnOverlap(CCollider* _pOther)
{
}

void CObj::EndOverlap(CCollider* _pOther)
{
}

