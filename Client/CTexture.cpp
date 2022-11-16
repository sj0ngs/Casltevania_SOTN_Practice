#include "pch.h"
#include "CTexture.h"

#include "CEngine.h"

CTexture::CTexture() :
	m_hBit(nullptr),
	m_hDC(nullptr),
	m_tBitMapInfo{},
	m_pBit(nullptr)
{
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBit);
}

int CTexture::Load(const wstring& _strFilePath)
{
	// Bitmap �ε�
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(m_hBit, sizeof(BITMAP), &m_tBitMapInfo);
	m_pBit = m_tBitMapInfo.bmBits;
	
	// Bitmap �� ���� ��ų DC ����
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBitmap);

	return S_OK;
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);

	// ������Ų ��Ʈ���� �������� �ϴ� DC�� ����
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBitmap);

	GetObject(m_hBit, sizeof(BITMAP), &m_tBitMapInfo);
}

void CTexture::Resize(UINT _iWidth, UINT _iHeight)
{
	// ���ο� ��Ʈ�ʰ� ���ο� dc �� ����
	HBITMAP hNewBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _iWidth, _iHeight);
	HDC hNewDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(hNewDC, hNewBit);
	DeleteObject(hPrevBitmap);

	// ������ �ִ� �׸��� ���ο� ������ ����
	BitBlt(hNewDC, 0, 0, m_tBitMapInfo.bmWidth, m_tBitMapInfo.bmHeight, m_hDC, 0, 0, SRCCOPY);

	// ���� ��Ʈ��, dc ����
	DeleteObject(m_hBit);
	DeleteDC(m_hDC);

	// ���ο� ��Ʈ��, dc�� ��ü
	m_hBit = hNewBit;
	m_hDC = hNewDC;

	GetObject(m_hBit, sizeof(BITMAP), &m_tBitMapInfo);
}


void CTexture::SetPixelColor(int _x, int _y, tPixel _pixel)
{
	_y = m_tBitMapInfo.bmHeight - (_y + 1);

	tPixel* pPixel = (tPixel*)m_pBit;
	pPixel += (m_tBitMapInfo.bmWidth * _y + _x);

	*pPixel = _pixel;
}

tPixel CTexture::GetPixelColor(int _x, int _y)
{
	// ���� ��Ʈ�� �ȼ��� �Ʒ��� ���� �����ϱ� ������,
	// ���������ͷ� ����ϴ� ������ ��ǥ��� ���߾��ֱ� ���ؼ� ���� ����� �����Ѵ�.
	_y = m_tBitMapInfo.bmHeight - (_y + 1);

	tPixel* pPixel = (tPixel*)m_pBit;
	pPixel += (m_tBitMapInfo.bmWidth * _y + _x);
	return *pPixel;
}
