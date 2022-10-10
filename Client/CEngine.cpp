#include "pch.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CResMgr.h"

#include "CTexture.h"

CEngine::CEngine()	:
	m_hMainWnd(nullptr),
	m_hDC(nullptr),
	m_pMemTex(nullptr),
	m_ptResolution{},
	m_arrPen{}
{
}

CEngine::~CEngine()
{
	ReleaseDC(m_hMainWnd, m_hDC);

	for (int i = 0; i < (UINT)EPEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void CEngine::Init(HWND _hwnd, UINT _iWidth, UINT _iHeight)
{
	m_hMainWnd = _hwnd;
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	// 윈도우 크기 설정
	RECT rt = {0, 0, (LONG)_iWidth, (LONG)_iHeight};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// HDC 초기화
	m_hDC = GetDC(m_hMainWnd);

	// 자주 사용하는 팬과 브러쉬를 세팅
	CreatePenBrush();

	// 백버퍼 용 텍스쳐 제작
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);

	CPathMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CLevelMgr::GetInst()->Init();
}

void CEngine::Tick()
{
	// FPS DeltaTime 계산
	CTimeMgr::GetInst()->Tick();
	CKeyMgr::GetInst()->Tick();

	CCamera::GetInst()->Tick();

	// Level 업데이트
	CLevelMgr::GetInst()->Tick();

	// 변경점 기반 충돌체크
	CCollisionMgr::GetInst()->Tick();
}

void CEngine::Render()
{
	// 이중 버퍼링으로 렌더링 해준다
	
	// 화면 클리어 작업
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// 레벨 랜더링
	CLevelMgr::GetInst()->Render(m_pMemTex->GetDC());

	// Camera Blind
	CCamera::GetInst()->Render(m_pMemTex->GetDC());

	// MemBitMap -> MainWindowBitMap 
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->Render();
}

void CEngine::CreatePenBrush()
{
	m_arrPen[(UINT)EPEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)EPEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)EPEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CEngine::Progress()
{
	// 논리적인 연산
	Tick();

	// 화면 랜더링 연산
	Render();

	CEventMgr::GetInst()->Tick();
}