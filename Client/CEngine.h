#pragma once

// 디자인 패턴 (설계 방식)

// 싱글톤 패턴
class CTexture;
class CEngine
{
	SINGLE(CEngine);

private:
	HWND m_hMainWnd;
	HDC m_hDC;

	CTexture* m_pMemTex;

	POINT m_ptResolution;

	HPEN m_arrPen[(UINT)EPEN_TYPE::END];

public:
	HWND GetMainWnd()	// 윈도우 핸들 리턴함수
	{
		return m_hMainWnd;
	}

	HPEN GetPen(EPEN_TYPE _Type)
	{
		return m_arrPen[(UINT)_Type];
	}

	HDC GetMainDC() { return m_hDC; }

	//HDC GetBackDC() { return m_pMemTex->GetDC(); }

	POINT GetResolution() { return m_ptResolution; }
private:
	void Tick();	// 갱신
	void Render();	// 랜더링
	void CreatePenBrush();

public:
	void Init(HWND _hwnd, unsigned int _iWidth, unsigned int _iHeight);
	void Progress();
};

