#include "pch.h"

#include "CSprialAxe.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CTrail.h"

CSprialAxe::CSprialAxe()	:
	m_fSpeed(50.f),
	m_fRadius(0.f),
    m_fAngle(0.f),
    m_fDegree(5.f),
    m_fAccTime(0.f),
    m_vCenter{},
    m_bOnThrow(false)
{
    CreateAnimator();

    //GetCollider()->SetScale(Vec2(100.f, 100.f));
    GetCollider()->SetScale(Vec2(0.f, 0.f));
    GetAnimator()->LoadAnimation(L"animation\\Weapon\\AXE_LEFT.anim");
    GetAnimator()->Play(true);
}

CSprialAxe::~CSprialAxe()
{
}

void CSprialAxe::Tick()
{
    CObj::Tick();

    if (m_bOnThrow)
    {
		m_fRadius += DELTATIME * 800.f;
		if (0.05f <= m_fAccTime)
		{
			CTrail* pTrail = new CTrail;
			pTrail->SetAnimFrm(GetAnimator()->GetCurAnimation()->GetCurFrm());
			pTrail->SetTrailTex(GetAnimator()->GetCurAnimation()->GetAltasTex());
			pTrail->SetLifeTime(0.4f);

			Instantiate(pTrail, GetPos(), ELAYER::EFFECT);

			m_fAccTime = 0.f;
		}

		m_fAccTime += DELTATIME;
    }
	else
	{
		m_fRadius = 100.f;
	}

	m_fAngle -= m_fDegree * DELTATIME * m_fSpeed;
	float fTheta = m_fAngle * PI / 180.f;

	Vec2 vPos = {};
	vPos.x = m_fRadius * cosf(fTheta) + m_vCenter.x;
	vPos.y = m_fRadius * sinf(fTheta) + m_vCenter.y;

	SetPos(vPos);

	MapOut();
}

void CSprialAxe::Render(HDC _DC)
{
	CObj::Render(_DC);
}

void CSprialAxe::BeginOverlap(CCollider* _pOther)
{
}
