#include "pch.h"
#include "CAxe.h"

#include "CAnimator.h"
#include "CRigidBody.h"
#include "CResMgr.h"
#include "CTexture.h"

#include "CAnimation.h"

#include "CTrail.h"


CAxe::CAxe()	:
	m_pLeftTex(nullptr),
	m_pRightTex(nullptr),
	m_faccTrailTime(0.f)
{
	CreateRigidBody();
	CreateAnimator();
	
	GetCollider()->SetScale(Vec2(100.f, 100.f));
	GetRigidBody()->SetGravity(true);
	GetRigidBody()->SetGravityAccel(2000.f);
	GetRigidBody()->SetMass(1.f);
	GetRigidBody()->SetFriction(100.f);

	GetAnimator()->LoadAnimation(L"animation\\Weapon\\AXE_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Weapon\\AXE_LEFT.anim");
}

CAxe::~CAxe()
{
}

void CAxe::Tick()
{
	if (0.2f <= m_faccTrailTime)
	{
		CTrail* pTrail = new CTrail;
		pTrail->SetAnimFrm(GetAnimator()->GetCurAnimation()->GetCurFrm());
		pTrail->SetTrailTex(GetAnimator()->GetCurAnimation()->GetAltasTex());
		pTrail->SetLifeTime(0.4f);

		Instantiate(pTrail, GetPos(), ELAYER::EFFECT);

		m_faccTrailTime = 0.f;
	}

	m_faccTrailTime += DELTATIME;

	MapOut();
}

void CAxe::Render(HDC _DC)
{
	CObj::Render(_DC);
}

void CAxe::BeginOverlap(CCollider* _pOther)
{
	CPlayerProjectile::BeginOverlap(_pOther);

	CObj* pObj = _pOther->GetOwner();

	if (ELAYER::MONSTER == pObj->GetLayer())
	{
		GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));

		if (GetFaceDir())
		{
			SetFaceDir(false);
			GetRigidBody()->AddVelocity(Vec2(-200.f, -500.f));
			GetAnimator()->Play(L"Axe_Left", true);
		}
		else
		{
			SetFaceDir(true);
			GetRigidBody()->AddVelocity(Vec2(200.f, -500.f));
			GetAnimator()->Play(L"Axe_Right", true);
		}
	}
}
