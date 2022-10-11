#include "pch.h"
#include "CTexture.h"

#include "CEngine.h"

CTexture::CTexture() :
	m_hBit(nullptr),
	m_hDC(nullptr),
	m_tBitMapInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBit);
}

int CTexture::Load(const wstring& _strFilePath)
{
	// Bitmap 로딩
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(m_hBit, sizeof(BITMAP), &m_tBitMapInfo);
	
	// Bitmap 과 연결 시킬 DC 생성
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBitmap);

	return S_OK;
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);

	// 생성시킨 비트맵을 목적지로 하는 DC를 생성
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBitmap);

	GetObject(m_hBit, sizeof(BITMAP), &m_tBitMapInfo);
}

void CTexture::Resize(UINT _iWidth, UINT _iHeight)
{
	// 새로운 비트맵과 새로운 dc 를 생성
	HBITMAP hNewBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);
	HDC hNewDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(hNewDC, hNewBit);
	DeleteObject(hPrevBitmap);

	// 기존에 있던 그림을 새로운 곳으로 복사
	BitBlt(hNewDC, 0, 0, m_tBitMapInfo.bmWidth, m_tBitMapInfo.bmHeight, m_hDC, 0, 0, SRCCOPY);

	// 기존 비트맵, dc 삭제
	DeleteObject(m_hBit);
	DeleteDC(m_hDC);

	// 새로운 비트맵, dc로 교체
	m_hBit = hNewBit;
	m_hDC = hNewDC;

	GetObject(m_hBit, sizeof(BITMAP), &m_tBitMapInfo);
}
