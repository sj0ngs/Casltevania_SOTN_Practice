#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CCollider.h"
#include "CTexture.h"

CMonster::CMonster()	:
	m_HP(3),
	m_pTarget(nullptr),
	m_fSpeed(100.f),
	m_pTexture(nullptr)
{
	CreateCollider();

	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	//m_pTexture = CResMgr::GetInst()->FindTexture(L"Plane");
	m_pTexture = CResMgr::GetInst()->FindTexture(L"Alucard");
}

CMonster::~CMonster()
{
}

void CMonster::Tick()
{
	if (IsValid(m_pTarget))
	{
		Vec2 vTargetPos = m_pTarget->GetPos();
		Vec2 vPos = GetPos();

		Vec2 vDir = vTargetPos - vPos;
		vDir.Normalize();

		vPos.x += vDir.x * m_fSpeed * DELTATIME;
		vPos.y += vDir.y * m_fSpeed * DELTATIME;

		SetPos(vPos);
	}

	CObj::Tick();
}

void CMonster::Render(HDC _DC)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
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
		tBlend);

	//BitBlt(_DC,
	//	(int)(vPos.x - m_pTexture->GetWidth() / 2.f),
	//	(int)(vPos.y - m_pTexture->GetHeight() / 2.f),
	//	(int)m_pTexture->GetWidth(), (int)m_pTexture->GetHeight(),
	//	m_pTexture->GetDC(),
	//	0, 0,
	//	SRCCOPY);

	CObj::Render(_DC);
}

void CMonster::BeginOverlap(CCollider* _pOther)
{
	SetDead();
}
