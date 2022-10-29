#include "pch.h"
#include "CAnimationEditor.h"

#include "resource.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CEventMgr.h"

#include "CLevel.h"
#include "CAnimationEditor.h"

#include "CAnimDebug.h"

#include "CAnimator.h"

#include "CTexture.h"
#include "CAnimation.h"


CAnimationEditor::CAnimationEditor()	:
	m_hMenu(nullptr),
	m_pDebugObj(nullptr),
	m_eMode(EANIMATION_MODE::ANIMATION),
	m_pAtlas(nullptr),
	m_bReverse(false),
	m_pAnim(nullptr),
	m_pvecFrm(nullptr),
	m_iCurFrm(0),	
	m_fDuration(0.f),
	m_iOffsetX(0),
	m_iOffsetY(0)
{
}

CAnimationEditor::~CAnimationEditor()
{
	if (nullptr != m_hMenu)
		DestroyMenu(m_hMenu);
}

void CAnimationEditor::Init()
{
	// 카메라 시점
	Vec2 vPos = CEngine::GetInst()->GetResolution();
	vPos /= 2.f;
	CCamera::GetInst()->SetLook(vPos);

	m_pDebugObj = new CAnimDebug;
	m_pDebugObj->SetName(L"Debug_Obj");
	m_pDebugObj->SetPos(vPos);

	AddObj(m_pDebugObj, ELAYER::PLAYER);

	//m_pAtlas = CResMgr::GetInst()->FindTexture(L"alucard_left_1");
	//m_pAtlas = CResMgr::GetInst()->FindTexture(L"alucard_left_2");
	//m_pAtlas = CResMgr::GetInst()->FindTexture(L"alucard_right_1");
}

void CAnimationEditor::Tick()
{
	CLevel::Tick();

	if (CEngine::GetInst()->GetMainWnd() == GetForegroundWindow())
	{	
		if (IS_TAP(EKEY::TAB))
		{
			ChangeLevel(ELEVEL_TYPE::EDITOR);
		}
		if (IS_TAP(EKEY::key1))
		{
			ChangeLevel(ELEVEL_TYPE::START);
		}
		Update();
	}
}

void CAnimationEditor::Render(HDC _DC)
{
	CLevel::Render(_DC);

	Vec2 vPos = CEngine::GetInst()->GetResolution();
	vPos /= 2.f;

	wstring strName = L"Animation Editor";
	TextOut(_DC, (int)vPos.x, 0, strName.c_str(), (int)strName.length());

	//if (nullptr != m_pAnim)
	//{
	//	strName = m_pAnim->GetName();

	//	TextOut(_DC, (int)vPos.x + 100, 100, strName.c_str(), (int)strName.length());
	//}
}

void CAnimationEditor::Enter()
{
	// 메뉴바 생성
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
	
	m_pDebugObj->GetAnimator()->SetCurAnim(nullptr);
	CLevel::DeleteAllObject();
}

void CAnimationEditor::Update()
{
	if (EANIMATION_MODE::FRAME == m_eMode)
		Frame_Update();
}

void CAnimationEditor::Frame_Update()
{
	if (m_pAnim == nullptr)
		return;

	if (IS_TAP(EKEY::LEFT))
	{
		m_pAnim->PrevFrame();
	}
	else if (IS_TAP(EKEY::RIGHT))
	{
		m_pAnim->NextFrame();
	}
	else if (IS_TAP(EKEY::SPACE))
	{
		m_pAnim->SwitchStop();
	}
	else if (IS_TAP(EKEY::LSHIFT))
	{
		m_pDebugObj->GetAnimator()->SwitchRepeat();
	}
	else if (IS_TAP(EKEY::R))
	{
		m_pAnim->Reset();
	}

	m_iCurFrm = m_pAnim->GetCurFrame();
}

void CAnimationEditor::SetAtlasTex()
{
	m_pAtlas = nullptr;

	// open a file name
	OPENFILENAME ofn = {};

	wstring strTextureFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTextureFolderPath += L"texture\\";

	// 탐색기로 설정한 위치의 경로 값이 들어간다
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// 파일 필터를 세팅할 수 있다
	ofn.lpstrFilter = L"texture\0*.bmp\0ALL\0*.*";
	// 최초에 보여줄 파일 세팅의 인덱스
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// 탐색기 창이 최초에 보여줄 경로, null로 하면 가장 최근에 접근한 경로를 보여준다
	ofn.lpstrInitialDir = strTextureFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	// 파일 탐색기는 전체 경로를 가져오기 때문에 컨텐츠 경로까지를 잘라준다
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	size_t start = strFilePath.length();
	wstring Buff = szFilePath;
	size_t end = Buff.length();
	wstring FilePath = Buff.substr(start, end);

	// 파일의 이름을 키 값으로 그대로 넣어준다
	wstring strKey = FilePath;

	// 확장자명 잘라주기
	for (size_t i = strKey.length(); i > 0; i--)
	{
		if (L'.' == strKey[i])
		{
			strKey[i] = 0;
			break;
		}
	}

	// 폴더 경로 짤라주기
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
	m_pAnim = nullptr;

	Vec2 vLEftTop = {};

	if (!_bReverse)
	{
		vLEftTop.x = (_vBorder.x + _vSize.x * iCol);
		vLEftTop.y = (_vBorder.y + _vSize.y * iRow);
	}
	else
	{
		float fWidth = (float)_pAtlas->GetWidth();
		vLEftTop.x = fWidth - (_vBorder.x + _vSize.x * (iCol + 1));
		vLEftTop.y = (_vBorder.y + _vSize.y * iRow);
		_vSize.x *= -1.f;
	}

	m_pDebugObj->GetAnimator()->CreateAnimation(_strName, _pAtlas, vLEftTop, _vSize, _iMaxFrmCount, _fDuration, _vPadding, _vOffset);
	m_pAnim = m_pDebugObj->GetAnimator()->FindAnimation(_strName);

	// open a file name
	OPENFILENAME ofn = {};

	wstring strAnimationFolderPath = CPathMgr::GetInst()->GetContentPath();
	strAnimationFolderPath += L"animation\\";

	// 탐색기로 설정한 위치의 경로 값이 들어간다
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// 파일 필터를 세팅할 수 있다
	ofn.lpstrFilter = L"animation\0*.anim\0ALL\0*.*";
	// 최초에 보여줄 파일 세팅의 인덱스
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// 탐색기 창이 최초에 보여줄 경로, null로 하면 가장 최근에 접근한 경로를 보여준다
	ofn.lpstrInitialDir = strAnimationFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	// 파일 탐색기는 전체 경로를 가져오기 때문에 컨텐츠 경로까지를 잘라준다
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	size_t start = strFilePath.length();
	wstring Buff = szFilePath;
	size_t end = Buff.length();
	wstring FilePath = Buff.substr(start, end);

	m_pAnim->Save(FilePath);

	m_pAnim = nullptr;
}

void CAnimationEditor::LoadAnim()
{
	m_pAnim = nullptr;

	// open a file name
	OPENFILENAME ofn = {};

	wstring strAnimationFolderPath = CPathMgr::GetInst()->GetContentPath();
	strAnimationFolderPath += L"animation\\";

	// 탐색기로 설정한 위치의 경로 값이 들어간다
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// 파일 필터를 세팅할 수 있다
	ofn.lpstrFilter = L"animation\0*.anim\0ALL\0*.*";
	// 최초에 보여줄 파일 세팅의 인덱스
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// 탐색기 창이 최초에 보여줄 경로, null로 하면 가장 최근에 접근한 경로를 보여준다
	ofn.lpstrInitialDir = strAnimationFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	// 파일 탐색기는 전체 경로를 가져오기 때문에 컨텐츠 경로까지를 잘라준다
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	size_t start = strFilePath.length();
	wstring Buff = szFilePath;
	size_t end = Buff.length();
	wstring FilePath = Buff.substr(start, end);

	m_pAnim = m_pDebugObj->GetAnimator()->LoadAnimation(FilePath);

	wstring strName = m_pAnim->GetName();
	m_pDebugObj->GetAnimator()->Play(strName, true);

	m_pvecFrm = m_pAnim->GetAnimFrame();
}

void CAnimationEditor::EditFrame()
{
	if (nullptr != m_pAnim)
	{
		(*m_pvecFrm)[m_iCurFrm].vOffset.x += m_iOffsetX;
		(*m_pvecFrm)[m_iCurFrm].vOffset.y += m_iOffsetY;

		for (size_t i = 0; i < (*m_pvecFrm).size(); i++)
		{
			if(0 != m_fDuration)
				(*m_pvecFrm)[i].fDuration = m_fDuration;
		}
	}

	m_iOffsetX = 0;
	m_iOffsetY = 0;
	m_fDuration = 0.f;
}

void CAnimationEditor::SaveAnim()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strAnimationFolderPath = CPathMgr::GetInst()->GetContentPath();
	strAnimationFolderPath += L"animation\\";

	// 탐색기로 설정한 위치의 경로 값이 들어간다
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// 파일 필터를 세팅할 수 있다
	ofn.lpstrFilter = L"animation\0*.anim\0ALL\0*.*";
	// 최초에 보여줄 파일 세팅의 인덱스
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// 탐색기 창이 최초에 보여줄 경로, null로 하면 가장 최근에 접근한 경로를 보여준다
	ofn.lpstrInitialDir = strAnimationFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	// 파일 탐색기는 전체 경로를 가져오기 때문에 컨텐츠 경로까지를 잘라준다
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	size_t start = strFilePath.length();
	wstring Buff = szFilePath;
	size_t end = Buff.length();
	wstring FilePath = Buff.substr(start, end);

	m_pAnim->Save(FilePath);
}

// =======================
// Anim Create Dialog Proc
// =======================
INT_PTR CALLBACK AnimCreate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	CAnimationEditor* pAnimEditor = dynamic_cast<CAnimationEditor*>(CLevelMgr::GetInst()->GetCurLevel());

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		if (nullptr == pAnimEditor)
		{
			DestroyWindow(hDlg);
			hDlg = nullptr;
			return (INT_PTR)FALSE;
		}

		pAnimEditor->ChangeMode(EANIMATION_MODE::ANIMATION);
		pAnimEditor->ResetAnim();
	}
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
			assert(pAnimEditor->GetAtlasTex());

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
			float fDuration = wcstof(szBuff, nullptr);
			memset(szBuff, sizeof(wchar_t), 256);

			Vec2 vPadding = {};
			vPadding.x = (float)GetDlgItemInt(hDlg, IDC_PADDING_X, nullptr, false);
			vPadding.y = (float)GetDlgItemInt(hDlg, IDC_PADDING_Y, nullptr, false);

			Vec2 vOffset = {}; 
			GetDlgItemText(hDlg, IDC_OFFSET_X, szBuff, 256);
			vOffset.x = wcstof(szBuff, nullptr);
			memset(szBuff, sizeof(wchar_t), 256);

			GetDlgItemText(hDlg, IDC_OFFSET_Y, szBuff, 256);
			vOffset.y = wcstof(szBuff, nullptr);
			memset(szBuff, sizeof(wchar_t), 256);

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

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		if (nullptr == pAnimEditor)
		{
			DestroyWindow(hDlg);
			hDlg = nullptr;
			return (INT_PTR)FALSE;
		}

		pAnimEditor->ChangeMode(EANIMATION_MODE::FRAME);
		pAnimEditor->ResetAnim();
		return (INT_PTR)TRUE;
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_LOAD_ANIM:
			pAnimEditor->LoadAnim();
			break;
		case IDC_CHANGE_DURATION:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				wchar_t szBuff[256];
				GetDlgItemText(hDlg, IDC_CHANGE_DURATION, szBuff, 256);
				float fDuration = wcstof(szBuff, nullptr);
				pAnimEditor->SetDuration(fDuration);
			}
			break;
			}
			break;
		case IDC_CHANGE_OFFSET_X:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				wchar_t szBuff[256];
				GetDlgItemText(hDlg, IDC_CHANGE_OFFSET_X, szBuff, 256);
				int iX = _wtoi(szBuff);
				pAnimEditor->SetOffsetX(iX);
			}
			break;
			}
			break;
		case IDC_CHANGE_OFFSET_Y:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				wchar_t szBuff[256];
				GetDlgItemText(hDlg, IDC_CHANGE_OFFSET_Y, szBuff, 256);
				int iY = _wtoi(szBuff);
				pAnimEditor->SetOffsetY(iY);
			}
			break;
			}
			break;
		case IDC_EDIT_FRM:
		{
			pAnimEditor->EditFrame();
		}
			break;
		case IDOK:
		{
			pAnimEditor->SaveAnim();
		}
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