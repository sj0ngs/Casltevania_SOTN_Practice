#include "pch.h"
#include "CBone.h"

#include "CRigidBody.h"
#include "CCollider.h"
#include "CAnimator.h"

CBone::CBone()
{
	CreateRigidBody();
	CreateAnimator();

	GetCollider()->SetScale(Vec2(64.f, 64.f));
	GetRigidBody()->SetGravity(true);
	GetRigidBody()->SetGravityAccel(2000.f);
	GetRigidBody()->SetMass(1.f);
	GetRigidBody()->SetFriction(100.f);

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Skeleton\\SKELETON_BONE_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Skeleton\\SKELETON_BONE_LEFT.anim");
}

CBone::~CBone()
{
}

void CBone::Tick()
{
	MapOut();
}

void CBone::Render(HDC _DC)
{
	CObj::Render(_DC);
}

void CBone::BeginOverlap(CCollider* _pOther)
{
	CMonsterProjectile::BeginOverlap(_pOther);
}
