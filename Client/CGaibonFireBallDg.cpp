#include "pch.h"
#include "CGaibonFireBallDg.h"

#include "CCollider.h"
#include "CAnimator.h"

CGaibonFireBallDg::CGaibonFireBallDg()	:
	m_fSpeed(200.f)
{
	CreateAnimator();

	GetCollider()->SetScale(Vec2(64.f, 64.f));

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_SMALL_FIRE_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_SMALL_FIRE_LEFT.anim");

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_FIRE_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Gaibon\\GAIBON_SKY_FIRE_LEFT.anim");
}

CGaibonFireBallDg::~CGaibonFireBallDg()
{

}

void CGaibonFireBallDg::Tick()
{
	Vec2 vPos = GetPos();

	if (GetFaceDir())
		vPos.x += m_fSpeed * DELTATIME;
	else
		vPos.x -= m_fSpeed * DELTATIME;

	vPos.y += m_fSpeed * DELTATIME;

	SetPos(vPos);

	MapOut();
}

void CGaibonFireBallDg::Render(HDC _DC)
{
	CObj::Render(_DC);
}

void CGaibonFireBallDg::BeginOverlap(CCollider* _pOther)
{
	CMonsterProjectile::BeginOverlap(_pOther);
}
