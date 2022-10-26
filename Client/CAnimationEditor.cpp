#include "pch.h"
#include "CAnimationEditor.h"

#include "resource.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"

#include "CLevel.h"
#include "CAnimationEditor.h"

#include "CAnimation.h"

CAnimationEditor::CAnimationEditor()	:
	m_hMenu(nullptr),
	m_eMode(EANIMATION_MODE::ANIMATION),
	m_pAtlas(nullptr),
	m_bReverse(false),
	m_pAnim(nullptr)
{
}

CAnimationEditor::~CAnimationEditor()
{
	if (nullptr != m_hMenu)
		DestroyMenu(m_hMenu);
}

void CAnimationEditor::Init()
{
}

void CAnimationEditor::Tick()
{
	CLevel::Tick();

	if (IS_TAP(EKEY::ENTER))
	{
		ChangeLevel(ELEVEL_TYPE::EDITOR);
	}
	if (IS_TAP(EKEY::key1))
	{
		ChangeLevel(ELEVEL_TYPE::START);
	}


	Update();
}

void CAnimationEditor::Enter()
{
	// �޴��� ����
	if (nullptr == m_hMenu)
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, m_hMenu);

	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);

	Init();
}

void CAnimationEditor::Exit()
{
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);

	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
}

void CAnimationEditor::Update()
{
	if (CEngine::GetInst()->GetMainWnd() == GetForegroundWindow())
	{
	}
}

void CAnimationEditor::SetAtlasTex()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTextureFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTextureFolderPath += L"texture\\";

	// Ž����� ������ ��ġ�� ��� ���� ����
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// ���� ���͸� ������ �� �ִ�
	ofn.lpstrFilter = L"texture\0*.bmp\0ALL\0*.*";
	// ���ʿ� ������ ���� ������ �ε���
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// Ž���� â�� ���ʿ� ������ ���, null�� �ϸ� ���� �ֱٿ� ������ ��θ� �����ش�
	ofn.lpstrInitialDir = strTextureFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	// ���� Ž����� ��ü ��θ� �������� ������ ������ ��α����� �߶��ش�
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	size_t start = strFilePath.length();
	wstring Buff = szFilePath;
	size_t end = Buff.length();
	wstring FilePath = Buff.substr(start, end);

	// ������ �̸��� Ű ������ �״�� �־��ش�
	wstring strKey = FilePath;

	// Ȯ���ڸ� �߶��ֱ�
	for (size_t i = strKey.length(); i > 0; i--)
	{
		if (L'.' == strKey[i])
		{
			strKey[i] = 0;
			break;
		}
	}

	// ���� ��� ©���ֱ�
	start = 0;
	end = strKey.length();

	for (size_t i = 0; i < end; i++)
	{
		if (L'\\' == strKey[i])
			start = i + 1;
	}
	strKey = strKey.substr(start, end);

	m_pAtlas = CResMgr::GetInst()->LoadTexture(strKey, FilePath);
}

void CAnimationEditor::CreateAnim(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vBorder,
	int iRow, int iCol, Vec2 _vSize, int _iMaxFrmCount, float _fDuration, Vec2 _vPadding, Vec2 _vOffset, bool _bReverse)
{
	m_pAnim->Init(_strName, _pAtlas, _vLeftTop, _vSize, _iMaxFrmCount, _fDuration, _vPadding, _vOffset);

	// open a file name
	OPENFILENAME ofn = {};

	wstring strAnimationFolderPath = CPathMgr::GetInst()->GetContentPath();
	strAnimationFolderPath += L"animation\\";

	// Ž����� ������ ��ġ�� ��� ���� ����
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// ���� ���͸� ������ �� �ִ�
	ofn.lpstrFilter = L"animation\0*.anim\0ALL\0*.*";
	// ���ʿ� ������ ���� ������ �ε���
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// Ž���� â�� ���ʿ� ������ ���, null�� �ϸ� ���� �ֱٿ� ������ ��θ� �����ش�
	ofn.lpstrInitialDir = strAnimationFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	// ���� Ž����� ��ü ��θ� �������� ������ ������ ��α����� �߶��ش�
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	size_t start = strFilePath.length();
	wstring Buff = szFilePath;
	size_t end = Buff.length();
	wstring FilePath = Buff.substr(start, end);

	m_pAnim->Save(FilePath);

	m_pAtlas = nullptr;
}

// =======================
// Anim Create Dialog Proc
// =======================
INT_PTR CALLBACK AnimCreate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	CAnimationEditor* pAnimEditor = dynamic_cast<CAnimationEditor*>(CLevelMgr::GetInst()->GetCurLevel());

	if (nullptr == pAnimEditor)
	{
		DestroyWindow(hDlg);
		hDlg = nullptr;
		return (INT_PTR)FALSE;
	}

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_LOAD_ATLAS)
		{
			pAnimEditor->SetAtlasTex();
		}
		else if (LOWORD(wParam) == IDC_REVERSE)
		{
			if (SendMessage((HWND)IDC_REVERSE, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
				pAnimEditor->SwtichReverse();
		}
		else if (LOWORD(wParam) == IDOK)
		{
			//if (!pAnimEditor->GetAtlasTex())
				//break;

			wchar_t szBuff[256];
			GetDlgItemText(hDlg, IDC_ANIM_NAME, szBuff, 256);
			wstring strName = szBuff;

			Vec2 vLeftTop = {};
			vLeftTop.x = (float)GetDlgItemInt(hDlg, IDC_LEFTTOP_X, nullptr, false);
			vLeftTop.y = (float)GetDlgItemInt(hDlg, IDC_LEFTTOP_Y, nullptr, false);

			Vec2 vBorder = {};
			vBorder.x = (float)GetDlgItemInt(hDlg, IDC_BORDER_X, nullptr, false);
			vBorder.y = (float)GetDlgItemInt(hDlg, IDC_BORDER_Y, nullptr, false);

			int iRow = GetDlgItemInt(hDlg, IDC_ROW, nullptr, true);
			int iCol = GetDlgItemInt(hDlg, IDC_COLUMN, nullptr, true);

			Vec2 vSize = {};
			vSize.x = (float)GetDlgItemInt(hDlg, IDC_SIZE_X, nullptr, false);
			vSize.y = (float)GetDlgItemInt(hDlg, IDC_SIZE_Y, nullptr, false);

			int iMaxFrmCount = GetDlgItemInt(hDlg, IDC_MAXFRMCOUNT, nullptr, true);

			GetDlgItemText(hDlg, IDC_DURATION, szBuff, 256);
			float fDuration = (float)_wtof(szBuff);

			Vec2 vPadding = {};
			vPadding.x = (float)GetDlgItemInt(hDlg, IDC_PADDING_X, nullptr, false);
			vPadding.y = (float)GetDlgItemInt(hDlg, IDC_PADDING_Y, nullptr, false);

			Vec2 vOffset = {};
			vOffset.x = (float)GetDlgItemInt(hDlg, IDC_OFFSET_X, nullptr, false);
			vOffset.y = (float)GetDlgItemInt(hDlg, IDC_OFFSET_Y, nullptr, false);

			bool bReverse = pAnimEditor->GetReverse();

			pAnimEditor->CreateAnim(strName, pAnimEditor->GetAtlasTex(), vLeftTop, vBorder, iRow, iCol, 
				vSize, iMaxFrmCount, fDuration, vPadding, vOffset, bReverse);

			pAnimEditor->OffReverse();
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


// =====================
// Anim Edit Dialog Proc
// =====================
INT_PTR CALLBACK AnimEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	CAnimationEditor* pAnimEditor = dynamic_cast<CAnimationEditor*>(CLevelMgr::GetInst()->GetCurLevel());

	if (nullptr == pAnimEditor)
	{
		DestroyWindow(hDlg);
		hDlg = nullptr;
		return (INT_PTR)FALSE;
	}

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		return (INT_PTR)TRUE;
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			break;
		case IDCANCEL:
			DestroyWindow(hDlg);
			hDlg = nullptr;
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}