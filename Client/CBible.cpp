#include "pch.h"
#include "CBible.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"

#include "CBibleTrail.h"

CBible::CBible() :
	m_fSpeed(100.f),
	m_fRadius(150.f),
	m_fAngle(0.f),
	m_fDegree(5.f),
	m_fAccTime(0.f),
	m_fSpawnTime(0.f),
	m_pCenter(nullptr),
	m_pTex(nullptr)
{
	GetCollider()->SetScale(Vec2(60.f, 80.f));
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Bible", L"texture\\Weapon\\Bible.bmp");
}

CBible::~CBible()
{
}

void CBible::Tick()
{		
	Vec2 vCenter;
	if (IsValid(m_pCenter))
	{
		vCenter = m_pCenter->GetPos();
		vCenter.y -= 100.f;
	}

	m_fAngle += m_fDegree * DELTATIME * m_fSpeed;
	float fTheta = m_fAngle * PI / 180.f;

	Vec2 vPos = {};
	vPos.x = m_fRadius * cosf(fTheta) + vCenter.x;
	vPos.y = m_fRadius * sinf(fTheta) + vCenter.y;

	SetPos(vPos);

	m_fAccTime += DELTATIME;
	m_fSpawnTime += DELTATIME;

	if (0.05f <= m_fSpawnTime)
	{
		CBibleTrail* pTrail = new CBibleTrail;
		Instantiate(pTrail, GetPos(), ELAYER::EFFECT);

		m_fSpawnTime = 0.f;
	}

	if (5.f <= m_fAccTime)
	{
		SetDead();
		return;
	}

	CObj::Tick();
}

void CBible::Render(HDC _DC)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_DC,
		(int)(vPos.x - m_pTex->GetWidth() / 2.f),
		(int)(vPos.y - m_pTex->GetHeight() / 2.f),
		(int)(m_pTex->GetWidth()),
		(int)(m_pTex->GetHeight()),
		m_pTex->GetDC(),
		0, 0,
		(int)(m_pTex->GetWidth()),
		(int)(m_pTex->GetHeight()),
		RGB(255, 0, 255));

	CObj::Render(_DC);
}

void CBible::BeginOverlap(CCollider* _pOther)
{
	CPlayerProjectile::BeginOverlap(_pOther);
}