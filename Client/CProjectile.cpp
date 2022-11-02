#include "pch.h"
#include "CProjectile.h"

CProjectile::CProjectile()	:
	m_iDmg(0)
{
	CreateCollider();
}

CProjectile::~CProjectile()
{
}

void CProjectile::Render(HDC _DC)
{
	CObj::Render(_DC);
}

