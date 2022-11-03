#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CCollider.h"
#include "CAI.h"

#include "CPlayer.h"

#include "CTexture.h"
#include "CState.h"
#include "CIdleState.h"
#include "CTraceState.h"

CMonster::CMonster()	:
	m_pTarget(nullptr),
	m_pTexture(nullptr),
	m_tInfo{}
{
	CreateCollider();
	CreateAI();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	GetAI()->AddState(L"Idle", new CIdleState);
	GetAI()->AddState(L"Trace", new CTraceState);
	GetAI()->ChangeState(L"Idle");

	m_tInfo.m_iMaxHP = 100;
	m_tInfo.m_iHP = m_tInfo.m_iMaxHP;
	m_tInfo.m_iAtk = 5;
	m_tInfo.m_fSpeed = 100.f;
	m_tInfo.m_fDetectRange = 200.f;
}

CMonster::~CMonster()
{
}

void CMonster::Tick()
{
	//if (IsValid(m_pTarget))
	//{
	//	Vec2 vTargetPos = m_pTarget->GetPos();
	//	Vec2 vPos = GetPos();

	//	Vec2 vDir = vTargetPos - vPos;
	//	vDir.Normalize();

	//	vPos.x += vDir.x * m_fSpeed * DELTATIME;
	//	vPos.y += vDir.y * m_fSpeed * DELTATIME;

	//	SetPos(vPos);
	//}

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
	
}

void CMonster::TakeDamage(int _iDmg)
{
	int iDamage = _iDmg - m_tInfo.m_iDef;

	if (0 >= iDamage)
		iDamage = 1;

	m_tInfo.m_iHP -= iDamage;

	if (0 > m_tInfo.m_iHP)
	{
		m_tInfo.m_iHP = 0;
		SetDead();
	}
	else if ((int)m_tInfo.m_iMaxHP < m_tInfo.m_iHP)
	{
		m_tInfo.m_iHP = m_tInfo.m_iMaxHP;
	}
}
