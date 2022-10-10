#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

#include "CCollider.h"

CMissile::CMissile()	:
	m_fSpeed(200.f),
	m_fDegree(90.f),
	m_fTime(0.f)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(10.f, 10.f));
}

CMissile::~CMissile()
{
}

void CMissile::Tick()
{
	Vec2 vPos = GetPos();
	
	// 60 분법 -> 라디안
	float fRadian = (m_fDegree * PI) / 180.f;

	vPos.x += m_fSpeed * cosf(fRadian) * DELTATIME;
	vPos.y -= m_fSpeed * sinf(fRadian) * DELTATIME;

	SetPos(vPos);

	m_fTime += DELTATIME;
	if (1.f < m_fTime)
	{
		// SetDead();
	}

	CObj::Tick();
}

void CMissile::Render(HDC _DC)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	Ellipse(_DC, (int)(vPos.x - vScale.x / 2),
		(int)(vPos.y - vScale.y / 2),
		(int)(vPos.x + vScale.x / 2),
		(int)(vPos.y + vScale.y / 2));

	CObj::Render(_DC);
}

void CMissile::BeginOverlap(CCollider* _pOther)
{
}
