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

	//float X = fabsf(m_tAnimFrm.vSize.x);

	//for (int i = (int)m_tAnimFrm.vLeftTop.x; i < (int)(m_tAnimFrm.vLeftTop.x + X); i++)
	//{
	//	for (int j = (int)m_tAnimFrm.vLeftTop.y; j < (int)(m_tAnimFrm.vLeftTop.y + m_tAnimFrm.vSize.y); j++)
	//	{
	//		tPixel tPixel = _pTex->GetPixelColor(i, j);
	//		if (0 != tPixel.a)
	//		{
	//			tPixel.b *= 2;
	//			m_pTex->SetPixelColor(i, j, tPixel);
	//		}
	//	}
	//}

	//wstring strName = m_pTex->GetName();

	//strName += L"_BackBuffer";

	//m_pTex = CResMgr::GetInst()->FindTexture(strName);

	//if (nullptr == m_pTex)
	//{
	//	m_pTex = CResMgr::GetInst()->CreateTexture(strName, _pTex->GetWidth(), _pTex->GetHeight());

	//	//m_hMemBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), (int)X, (int)m_tAnimFrm.vSize.y);
	//	//m_hMemDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	//	//HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hMemBit);
	//	//DeleteObject(hPrevBitmap);

	//	TransparentBlt(m_pTex->GetDC(),
	//		(int)(m_tAnimFrm.vLeftTop.x), (int)(m_tAnimFrm.vLeftTop.y),
	//		(int)(X), (int)(m_tAnimFrm.vSize.y),
	//		_pTex->GetDC(),
	//		(int)(m_tAnimFrm.vLeftTop.x), (int)(m_tAnimFrm.vLeftTop.y),
	//		(int)(X), (int)(m_tAnimFrm.vSize.y),
	//		RGB(255, 0, 255));

	//	BitBlt(m_pTex->GetDC(),
	//		0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(),
	//		_pTex->GetDC(),
	//		_pTex->GetWidth(), _pTex->GetHeight(),
	//		SRCCOPY);

	//	m_pTex->SetpBit();

	//	//for (int i = (int)m_tAnimFrm.vLeftTop.x; i < (int)(m_tAnimFrm.vLeftTop.x + X); i++)
	//	//{
	//	//	for (int j = (int)m_tAnimFrm.vLeftTop.y; j < (int)(m_tAnimFrm.vLeftTop.y + m_tAnimFrm.vSize.y); j++)
	//	//	{
	//	//		tPixel tPixel = _pTex->GetPixelColor(i, j);
	//	//		if (0 != tPixel.a)
	//	//		{
	//	//			tPixel.b *= 2;
	//	//			m_pTex->SetPixelColor(i, j, tPixel);
	//	//		}
	//	//	}
	//	//}

	//	for (int i = 0; i < (int)(m_pTex->GetWidth()); i++)
	//	{
	//		for (int j = 0; j < (int)(m_pTex->GetHeight()); j++)
	//		{
	//			tPixel tPixel = _pTex->GetPixelColor(i, j);
	//			if (0 != tPixel.a)
	//			{
	//				tPixel.b *= 2;
	//				m_pTex->SetPixelColor(i, j, tPixel);
	//			}
	//		}
	//	}
	//}	
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
