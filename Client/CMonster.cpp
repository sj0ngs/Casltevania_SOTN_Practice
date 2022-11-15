#include "pch.h"
#include "CMonster.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CCollider.h"
#include "CAI.h"

#include "CPlayer.h"

#include "CTexture.h"
#include "CDeadState.h"

#include "CProjectile.h"

#include "CSound.h"

CMonster::CMonster()	:
	m_tInfo{},
	m_bOnAttack(false)
{
	CreateCollider();
	CreateAnimator();
	CreateRigidBody();
	CreateAI();
	
	GetRigidBody()->SetGravity(true);
	GetRigidBody()->SetGravityAccel(1000.f);

	GetAI()->AddState(L"Dead", new CDeadState);
}

CMonster::~CMonster()
{
}

void CMonster::Tick()
{
	CObj::Tick();
}

void CMonster::Render(HDC _DC)
{
	/*Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	static float fRatio = 0.f;
	static float Dir = 1;
	fRatio += DELTATIME * Dir * 3;

	if (1.f <= fRatio)
	{
		Dir = -1.f;
		fRatio = 1.f;
	}
	else if (0 >= fRatio)
	{
		Dir = 1.f;
		fRatio = 0.f;
	}

	BLENDFUNCTION tBlend = {};
	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255 * fRatio);

	AlphaBlend(_DC,
		(int)(vPos.x - m_pTexture->GetWidth() / 2.f),
		(int)(vPos.y - m_pTexture->GetHeight() / 2.f),
		(int)m_pTexture->GetWidth(), (int)m_pTexture->GetHeight(),
		m_pTexture->GetDC(),
		0, 0,
		(int)m_pTexture->GetWidth(), (int)m_pTexture->GetHeight(),
		tBlend);*/

	//BitBlt(_DC,
	//	(int)(vPos.x - m_pTexture->GetWidth() / 2.f),
	//	(int)(vPos.y - m_pTexture->GetHeight() / 2.f),
	//	(int)m_pTexture->GetWidth(), (int)m_pTexture->GetHeight(),
	//	m_pTexture->GetDC(),
	//	0, 0,
	//	SRCCOPY);

	CObj::Render(_DC);

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	wstring strHp = L"HP : ";
	strHp += std::to_wstring(m_tInfo.m_iHP);

	TextOut(_DC, (int)vPos.x, (int)vPos.y, strHp.c_str(), (int)strHp.length());
}

void CMonster::BeginOverlap(CCollider* _pOther)
{
	CObj* pObj = _pOther->GetOwner();

	if (ELAYER::PLAYER_PROJECTILE == pObj->GetLayer())
	{
		CProjectile* pProjectile = (CProjectile*)pObj;

		TakeDamage(pProjectile->GetDamage());

		PLAY_SOUND(L"Hit");
	}
}

void CMonster::TakeDamage(int _iDmg)
{
	int iDamage = _iDmg - m_tInfo.m_iDef;

	if (0 >= iDamage)
		iDamage = 1;

	m_tInfo.m_iHP -= iDamage;

	if (0 >= m_tInfo.m_iHP)
	{
		m_tInfo.m_iHP = 0;
	}
	else if ((int)m_tInfo.m_iMaxHP < m_tInfo.m_iHP)
	{
		m_tInfo.m_iHP = m_tInfo.m_iMaxHP;
	}
}

void CMonster::Turn()
{
	bool bFaceDir = GetFaceDir();

	bFaceDir = bFaceDir ? false : true;
	SetFaceDir(bFaceDir);
}
