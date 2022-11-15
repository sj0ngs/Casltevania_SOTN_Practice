#include "pch.h"

#include "CObj.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"

#include "CComponent.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CAI.h"

// 오브젝트 dead 처리 함수
void CObj::SetDead()
{
	if (this->IsDead())
		return;

	tEvent evn = {};
	evn.eType = EEVENT_TYPE::DELETE_OBJECT;
	evn.wParam = (DWORD_PTR)this;
	CEventMgr::GetInst()->AddEvent(evn);
}

CObj::CObj() :
	m_vPos{},
	m_vScale{},
	m_eLayer(ELAYER::END),
	m_vDir(1.f, 0.f),
	m_bFaceDir(true),
	m_pCollider(nullptr),
	m_pAnimator(nullptr),
	m_pRigidBody(nullptr),
	m_pAI(nullptr),
	m_bDead(false)
{
}

CObj::CObj(const CObj& _Other)	:
	CEntity(_Other),
	m_vPos(_Other.m_vPos),
	m_vScale(_Other.m_vScale),
	m_eLayer(_Other.m_eLayer),
	m_vDir(1.f, 0.f),
	m_bFaceDir(_Other.m_bFaceDir),
	m_pCollider(nullptr),
	m_pAnimator(nullptr),
	m_pRigidBody(nullptr),
	m_pAI(nullptr),
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

	if (nullptr != _Other.m_pAI)
	{
		m_pAI = _Other.m_pAI->Clone();
		m_pAI->SetOwner(this);
	}
}

CObj::~CObj()
{
	DYNAMIC_DELETE(m_pCollider);
	DYNAMIC_DELETE(m_pAnimator);
	DYNAMIC_DELETE(m_pRigidBody);
	DYNAMIC_DELETE(m_pAI);
}

void CObj::Tick()
{
	if (nullptr != m_pCollider)
		m_pCollider->Tick();

	if (nullptr != m_pAnimator)
		m_pAnimator->Tick();

	if (nullptr != m_pAI)
		m_pAI->Tick();

	if (nullptr != m_pRigidBody)
		m_pRigidBody->Tick();
}

void CObj::Final_Tick()
{
	if (nullptr != m_pRigidBody)
		m_pRigidBody->Final_Tick();

	if (nullptr != m_pAI)
		m_pAI->Final_Tick();

	if (nullptr != m_pAnimator)
		m_pAnimator->Final_Tick();

	if (nullptr != m_pCollider)
		m_pCollider->Final_Tick();
}

void CObj::Render(HDC _DC)
{
	if (nullptr != m_pAnimator)
		m_pAnimator->Render(_DC);

	if (nullptr != m_pCollider)
		m_pCollider->Render(_DC);

	m_PrevPos = m_vPos;
}

void CObj::CreateCollider()
{
	m_pCollider = new CCollider(this);
}

void CObj::CreateAnimator()
{
	m_pAnimator = new CAnimator(this);
}

void CObj::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody(this);
}

void CObj::CreateAI()
{
	m_pAI = new AI(this);
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

