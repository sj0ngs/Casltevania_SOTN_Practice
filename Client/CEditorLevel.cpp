#include "pch.h"
#include "CEditorLevel.h"

#include "resource.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CLevelMgr.h"
#include "CPathMgr.h"

#include "CBackGround.h"
#include "CPlatform.h"

#include "CCollider.h"
#include "CTexture.h"
#include "CTile.h"
#include "CUI.h"
#include "CButton.h"

CEditorLevel::CEditorLevel()	:
	m_hMenu(nullptr),
	m_eMode(EEDITOR_MODE::FLOOR),
	m_eFloorOption(EFLOOR_OPTION::FLOOR),
	m_eObjectOption(EOBJ_OPTION::SPAWN_POINT),
	m_vMousePos1{-1.f, -1.f}
{
}

CEditorLevel::~CEditorLevel()
{
	if(nullptr != m_hMenu)
		DestroyMenu(m_hMenu);
}

void CEditorLevel::Tick()
{
	CLevel::Tick();

	if (IS_TAP(EKEY::ENTER))
	{
		ChangeLevel(ELEVEL_TYPE::START);
	}

	Update();
}

void CEditorLevel::Enter()
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

void CEditorLevel::Exit()
{
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);

	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);
}

void CEditorLevel::Update()
{
	if (CEngine::GetInst()->GetMainWnd() == GetForegroundWindow())
	{
		switch (m_eMode)
		{
		case EEDITOR_MODE::FLOOR:
			Map_Update();
			break;
		case EEDITOR_MODE::OBJECT:
			Object_Update();
			break;
		}
	}
}

void CEditorLevel::Object_Update()
{
}

void CEditorLevel::SaveTile()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"tile\\";

	// 탐색기로 설정한 위치의 경로 값이 들어간다
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// 파일 필터를 세팅할 수 있다
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	// 최초에 보여줄 파일 세팅의 인덱스
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// 탐색기 창이 최초에 보여줄 경로, null로 하면 가장 최근에 접근한 경로를 보여준다
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");

	if (nullptr != pFile)
	{
		// 타일 가로 새로 개수 저장
		UINT iTileXCount = GetTileXCount();
		UINT iTileYCount = GetTileYCount();

		fwrite(&iTileXCount, sizeof(UINT), 1, pFile);
		fwrite(&iTileYCount, sizeof(UINT), 1, pFile);

		const vector<CObj*>& vecTile = GetLayer(ELAYER::TILE);
		for (size_t i = 0; i < vecTile.size(); i++)
		{
			((CTile*)vecTile[i])->Save(pFile);
		}

		fclose(pFile);
	}
}

void CEditorLevel::LoadTile()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"tile\\";

	// 탐색기로 설정한 위치의 경로 값이 들어간다
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// 파일 필터를 세팅할 수 있다
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	// 최초에 보여줄 파일 세팅의 인덱스
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// 탐색기 창이 최초에 보여줄 경로, null로 하면 가장 최근에 접근한 경로를 보여준다
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");
	
	if (nullptr != pFile)
	{
		// 타일 가로 새로 불러오고 타일 생성
		UINT iTileXCount = 0, iTileYCount = 0;

		fread(&iTileXCount, sizeof(UINT), 1, pFile);
		fread(&iTileYCount, sizeof(UINT), 1, pFile);

		CreateTile(iTileXCount, iTileYCount);

		const vector<CObj*>& vecTile = GetLayer(ELAYER::TILE);
		for (size_t i = 0; i < vecTile.size(); i++)
		{
			((CTile*)vecTile[i])->Load(pFile);
		}

		fclose(pFile);
	}
}

void CEditorLevel::SaveLevel()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"level\\";

	// 탐색기로 설정한 위치의 경로 값이 들어간다
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// 파일 필터를 세팅할 수 있다
	ofn.lpstrFilter = L"Level\0*.level\0ALL\0*.*";
	// 최초에 보여줄 파일 세팅의 인덱스
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// 탐색기 창이 최초에 보여줄 경로, null로 하면 가장 최근에 접근한 경로를 보여준다
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");

	if (nullptr != pFile)
	{
		SaveBackGround(pFile);
		SaveForeGround(pFile);
		SavePlatform(pFile);
		SaveLine(pFile);

		fclose(pFile);
	}
}

void CEditorLevel::LoadLevel()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"level\\";

	// 탐색기로 설정한 위치의 경로 값이 들어간다
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// 파일 필터를 세팅할 수 있다
	ofn.lpstrFilter = L"Level\0*.level\0ALL\0*.*";
	// 최초에 보여줄 파일 세팅의 인덱스
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// 탐색기 창이 최초에 보여줄 경로, null로 하면 가장 최근에 접근한 경로를 보여준다
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");

	if (nullptr != pFile)
	{
		LoadBackGround(pFile);
		LoadForeGround(pFile);

		// 불러온 파일에 맞는 타일 그리드를 깔아줘야 다시 편집이 가능하다
		const vector<CObj*> vecForeGround = GetLayer(ELAYER::FOREGROUND);
		CBackGround* pForeGround = (CBackGround*)vecForeGround[0];
		const CTexture* pForeGroundImg = pForeGround->GetTex();

		if (nullptr != pForeGroundImg)
		{
			// 로드한 이미지의 사이즈에 맞게 그리드 타일을 배치
			float iRow = round(pForeGroundImg->GetWidth() / (float)TILE_SIZE);
			float iCol = round(pForeGroundImg->GetHeight() / (float)TILE_SIZE);
			CreateTile((UINT)iRow, (UINT)iCol);
		}

		LoadPlatform(pFile);
		LoadLine(pFile);

		fclose(pFile);
	}
}

// ======================
// Tile Count Dialog Proc
// ======================
INT_PTR CALLBACK TileCount(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// edit control에서 입력된 숫자 받아오기
			int iTileXCount =  GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int iTileYCount =  GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);

			if (!(iTileXCount && iTileYCount))
			{
				MessageBox(nullptr, L"타일 개수를 지정하세요.", L"타일 생성 오류", MB_OK);
				return (INT_PTR)TRUE;
			}

			// 지정된 숫자로 타일을 새로 생성한다
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			pCurLevel->CreateTile(iTileXCount, iTileYCount);

			// 각 타일에다가 사용할 아틀라스 이미지 및 인덱스 설정
			CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");

			const vector<CObj*>& vecTile = pCurLevel->GetLayer(ELAYER::TILE);
			for (size_t i = 0; i < vecTile.size(); i++)
			{
				((CTile*)vecTile[i])->SetAtlas(pTex);
				((CTile*)vecTile[i])->SetImgIdx(0);
			}

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if(LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
