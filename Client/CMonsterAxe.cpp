#include "pch.h"
#include "CMonsterAxe.h"

#include "CTimeMgr.h"

#include "CCollider.h"
#include "CAnimator.h"

CMonsterAxe::CMonsterAxe()	:
	m_fSpeed(400.f),
	m_faccTurnTime(0.f),
	m_bIsTurn(false)
{
	CreateAnimator();

	GetCollider()->SetScale(Vec2(64.f, 64.f));

	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_AXE_RIGHT.anim");
	GetAnimator()->LoadAnimation(L"animation\\Monster\\Axe_Armor\\AXE_ARMOR_AXE_LEFT.anim");
}

CMonsterAxe::~CMonsterAxe()
{
}

void CMonsterAxe::Tick()
{
	Vec2 vPos = GetPos();

	if (GetFaceDir())
	{
		vPos.x += m_fSpeed * DELTATIME;
	}
	else
	{
		vPos.x -= m_fSpeed * DELTATIME;
	}

	if (!m_bIsTurn)
	{
		if (2.f < m_faccTurnTime)
		{
			Turn();
		}
		m_faccTurnTime += DELTATIME;
	}

	SetPos(vPos);

	MapOut();
}

void CMonsterAxe::Render(HDC _DC)
{
	CObj::Render(_DC);
}

void CMonsterAxe::BeginOverlap(CCollider* _pOther)
{
	CMonsterProjectile::BeginOverlap(_pOther);
}

void CMonsterAxe::Turn()
{
	m_bIsTurn = true;
	if (GetFaceDir())
	{
		SetFaceDir(false);
		GetAnimator()->Play(L"Axe_Armor_Axe_Left", true);
	}
	else
	{
		SetFaceDir(true);
		GetAnimator()->Play(L"Axe_Armor_Axe_Right", true);
	}
}
