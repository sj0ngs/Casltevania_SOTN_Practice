#include "pch.h"
#include "CGaibonFireBall.h"

#include "CCollider.h"
#include "CAnimator.h"

CGaibonFireBall::CGaibonFireBall()	:
	m_fSpeed(200.f)
{
	CreateAnimator();

	GetCollider()->SetScale(Vec2(64.f, 64.f));

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_LAND_FIRE_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\Gaibon_Land_Fire_Left.anim");
}

CGaibonFireBall::~CGaibonFireBall()
{
}

void CGaibonFireBall::Tick()
{
	Vec2 vPos = GetPos();

	if (GetFaceDir())
		vPos.x += m_fSpeed * DELTATIME;
	else
		vPos.x -= m_fSpeed * DELTATIME;

	SetPos(vPos);

	MapOut();
}

void CGaibonFireBall::Render(HDC _DC)
{
	CObj::Render(_DC);
}

void CGaibonFireBall::BeginOverlap(CCollider* _pOther)
{
	CMonsterProjectile::BeginOverlap(_pOther);
}
