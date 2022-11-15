#include "pch.h"
#include "CSlograDropState.h"

#include "CResMgr.h"

#include "CCamera.h"

#include "CSlogra.h"

#include "CSound.h"

CSlograDropState::CSlograDropState()	:
	m_faccGroundTime(0.f),
	m_bIsGround(false),
	m_bColliderChanged(false)
{
}

CSlograDropState::~CSlograDropState()
{
}

void CSlograDropState::Final_Tick()
{
	CSlogra* pSlogra = (CSlogra*)GetOwnerObj();

	if (!pSlogra->IsSlograCatch())
	{
		pSlogra->GetRigidBody()->SetGravity(true);
	}

	if (ESLOGRA_STATE::BEAK == pSlogra->GetSlograState() && 
		!m_bColliderChanged && 
		3 == pSlogra->GetAnimator()->GetCurAnimation()->GetCurFrame())
	{
		pSlogra->GetCollider()->SetScale(Vec2(270.f, 150.f));

		if (pSlogra->GetFaceDir())
		{
			pSlogra->GetCollider()->SetOffsetPos(Vec2(100.f, -75.f));
		}
		else
		{
			pSlogra->GetCollider()->SetOffsetPos(Vec2(-100.f, -75.f));
		}
	}

	if (!m_bIsGround && pSlogra->GetRigidBody()->IsGround())
	{
		m_bIsGround = true;
		CCamera::GetInst()->CameraShake(1.f, 2, 100.f);

		PLAY_SOUND(L"GOLEM_MOVE1");
	}

	if (m_bIsGround)
	{
		m_faccGroundTime += DELTATIME;

		if (0.1f <= m_faccGroundTime)
		{
			ChangeState(L"SlograIdle");
		}
	}

	Dead();
}

void CSlograDropState::Enter()
{
	CSlogra* pSlogra = (CSlogra*)GetOwnerObj();

	pSlogra->Drop();
	m_bIsGround = false;

	pSlogra->GetRigidBody()->SetGravity(false);
	pSlogra->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
}

void CSlograDropState::Exit()
{
	CSlogra* pSlogra = (CSlogra*)GetOwnerObj();
	m_faccGroundTime = 0.f;

	pSlogra->GetCollider()->SetScale(Vec2(70.f, 220.f));
	pSlogra->GetCollider()->SetOffsetPos(Vec2(0.f, -110.f));

	m_bColliderChanged = false;
}
