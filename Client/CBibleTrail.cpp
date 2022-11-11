#include "pch.h"
#include "CBibleTrail.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CTexture.h"

CBibleTrail::CBibleTrail()	:
	m_fLifeTime(0.f),
	m_pTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->FindTexture(L"Bible_Trail");
}

CBibleTrail::~CBibleTrail()
{
}

void CBibleTrail::Tick()
{
	m_fLifeTime += DELTATIME;

	if (0.2f <= m_fLifeTime)
		SetDead();
}

void CBibleTrail::Render(HDC _DC)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	float fRatio = ((0.25f - m_fLifeTime) / 0.25f);

	BLENDFUNCTION tBlend = {};
	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255 * fRatio);

	AlphaBlend(_DC,
		(int)(vPos.x - m_pTex->GetWidth() / 2.f),
		(int)(vPos.y - m_pTex->GetHeight() / 2.f),
		(int)m_pTex->GetWidth(), (int)m_pTex->GetHeight(),
		m_pTex->GetDC(),
		0, 0,
		(int)m_pTex->GetWidth(), (int)m_pTex->GetHeight(),
		tBlend);
}
