#include "pch.h"
#include "CTimeMgr.h"
#include "CEngine.h"

CTimeMgr::CTimeMgr() :
	m_llPrevCount{},
	m_llCurCount{},
	m_llFrequency{},
	m_iFPS(0),
	m_fDeltaTime(0.f),
	m_fTime(0.f)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Init()
{
	// 1초당 카운팅 증가량
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceCounter(&m_llCurCount);
}

void CTimeMgr::Tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_fDeltaTime = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	m_fTime += m_fDeltaTime;

	++m_iFPS;

	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::Render()
{
	if (1.f <= m_fTime)
	{
		wchar_t szBuff[256] = {};
		swprintf_s(szBuff, L"FPS : %d, Delta Time : %f", m_iFPS, m_fDeltaTime);
		SetWindowText(CEngine::GetInst()->GetMainWnd(), szBuff);

		m_fTime = 0;
		m_iFPS = 0;
	}
}
