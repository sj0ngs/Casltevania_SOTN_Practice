#include "pch.h"
#include "CTrail.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CTexture.h"

void CTrail::SetTrailTex(CTexture* _pTex)
{
	wstring strName = _pTex->GetKey();
	strName += L"_Trail";
	m_pTex = CResMgr::GetInst()->FindTexture(strName);
	assert(m_pTex);
}

CTrail::CTrail()	:
	m_pTex(nullptr),
	m_tAnimFrm{},
	m_faccLifeTime(0.f),
	m_fLifeTime(1.f),
	m_tBlend{},
	m_fRatio(0.8f)
{
	m_tBlend.AlphaFormat = AC_SRC_ALPHA;
	m_tBlend.BlendFlags = 0;
	m_tBlend.BlendOp = AC_SRC_OVER;
	m_tBlend.SourceConstantAlpha = (int)(255 * m_fRatio);
}

CTrail::~CTrail()
{
}

void CTrail::Tick()
{
	if (m_fLifeTime <= m_faccLifeTime)
	{
		SetDead();
		return;
	}

	m_faccLifeTime += DELTATIME;
}

void CTrail::Render(HDC _DC)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	float X = fabsf(m_tAnimFrm.vSize.x);

	m_fRatio = 1.1f - m_faccLifeTime / m_fLifeTime;

	m_tBlend.SourceConstantAlpha = (int)(255 * m_fRatio);

	AlphaBlend(_DC,
		(int)(vPos.x - X / 2.f + m_tAnimFrm.vOffset.x),
		(int)(vPos.y - m_tAnimFrm.vSize.y / 2.f + m_tAnimFrm.vOffset.y),
		(int)(X), (int)(m_tAnimFrm.vSize.y),
		m_pTex->GetDC(),
		(int)(m_tAnimFrm.vLeftTop.x), (int)(m_tAnimFrm.vLeftTop.y),
		(int)(X), (int)(m_tAnimFrm.vSize.y),
		m_tBlend);
}
