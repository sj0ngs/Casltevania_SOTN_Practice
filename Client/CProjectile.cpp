#include "pch.h"
#include "CProjectile.h"

#include "CLevelMgr.h"
#include "CLevel.h"

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

void CProjectile::MapOut()
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurLevel();

	Vec2 vPos = GetPos();
	UINT iWidth = pLevel->GetLevelWidth();
	UINT iHeight = pLevel->GetLevelHeight();

	if (0 > vPos.x || iWidth < vPos.x || 0 > vPos.y || iHeight < vPos.y)
	{
		SetDead();
	}
}

void CProjectile::Dead()
{
	SetDead();
}

