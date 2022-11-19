#include "pch.h"
#include "CLetter.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CTexture.h"

CLetter::CLetter()	:
	m_pTex(nullptr),
	m_faccTime(0.f),
	m_fLifeTime(1.f),
	m_tBlend{}
{
	m_tBlend.AlphaFormat = AC_SRC_ALPHA;
	m_tBlend.BlendFlags = 0;
	m_tBlend.BlendOp = AC_SRC_OVER;
	m_tBlend.SourceConstantAlpha = (int)(255);
}

CLetter::~CLetter()
{
}

void CLetter::Tick()
{
	Vec2 vPos = GetPos();

	vPos.y -= 20.f * DELTATIME;

	m_faccTime += DELTATIME;

	if (m_fLifeTime <= m_faccTime)
	{
		SetDead();
	}

	SetPos(vPos);
}

void CLetter::Render(HDC _DC)
{
	if (nullptr != m_pTex)
	{
		Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

		float _fRatio = 1.1f - m_faccTime / m_fLifeTime;

		m_tBlend.SourceConstantAlpha = (int)(255 * _fRatio);

		AlphaBlend(_DC,
			(int)(vPos.x - m_pTex->GetWidth() / 2.f), 
			(int)(vPos.y - m_pTex->GetWidth() / 2.f),
			m_pTex->GetWidth(), m_pTex->GetHeight(),
			m_pTex->GetDC(),
			0, 0,
			m_pTex->GetWidth(), m_pTex->GetHeight(),
			m_tBlend);
	}
}
