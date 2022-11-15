#include "pch.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CLineCollisionMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CResMgr.h"
#include "CUIMgr.h"
#include "CObjMgr.h"
#include "CSoundMgr.h"

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

	// HDC �ʱ�ȭ
	m_hDC = GetDC(m_hMainWnd);

	// ������ ũ�� ����
	ChangeWindowSize(m_ptResolution.x, m_ptResolution.y);

	// ���� ����ϴ� �Ұ� �귯���� ����
	CreatePenBrush();

	CPathMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CSoundMgr::GetInst()->Init();
	CResMgr::GetInst()->Init();
	CObjMgr::GetInst()->Init();
	CLevelMgr::GetInst()->Init();
}

void CEngine::Tick()
{
	// FPS DeltaTime ���
	CTimeMgr::GetInst()->Tick();
	CKeyMgr::GetInst()->Tick();

	CCamera::GetInst()->Tick();

	// Level ������Ʈ
	CLevelMgr::GetInst()->Tick();

	// ������ ��� �浹üũ
	CLineCollisionMgr::GetInst()->Tick();
	CCollisionMgr::GetInst()->Tick();

	// UI ó��
	CUIMgr::GetInst()->Tick();
}

void CEngine::Render()
{
	// ���� ���۸����� ������ ���ش�
	
	// ȭ�� Ŭ���� �۾�
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// ���� ������
	CLevelMgr::GetInst()->Render(m_pMemTex->GetDC());

	// Camera Blind
	CCamera::GetInst()->Render(m_pMemTex->GetDC());

	// MemBitMap -> MainWindowBitMap 
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->Render();
}

void CEngine::Progress()
{
	// ������ ����
	Tick();

	// ȭ�� ������ ����
	Render();
	
	CEventMgr::GetInst()->Tick();
}

void CEngine::CreatePenBrush()
{
	m_arrPen[(UINT)EPEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)EPEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)EPEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void CEngine::ChangeWindowSize(UINT _iWidth, UINT _iHeight)
{
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };

	HMENU hMenu = GetMenu(m_hMainWnd);

	if(nullptr != hMenu)
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	else
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(m_hMainWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// ����۰� ������ ����
	if (nullptr == m_pMemTex)
	{
		// ����� �� �ؽ��� ����
		m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);
	}
	// ����۰� ������ ������ ����
	else
		m_pMemTex->Resize(m_ptResolution.x, m_ptResolution.y);
}

