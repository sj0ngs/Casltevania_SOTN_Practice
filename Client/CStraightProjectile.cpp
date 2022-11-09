#include "pch.h"
#include "CStraightProjectile.h"

CStraightProjectile::CStraightProjectile()	:
	m_fSpeed(100.f)
{
	CreateAnimator();
}

CStraightProjectile::~CStraightProjectile()
{
}

void CStraightProjectile::Tick()
{
	Vec2 vPos = GetPos();

	if (GetFaceDir())
		vPos.x += m_fSpeed * DELTATIME;
	else
		vPos.x -= m_fSpeed * DELTATIME;

	SetPos(vPos);

	MapOut();
}

void CStraightProjectile::Render(HDC _DC)
{
	CObj::Render(_DC);
}

void CStraightProjectile::BeginOverlap(CCollider* _pOther)
{
	CMonsterProjectile::BeginOverlap(_pOther);
}
