#include "pch.h"
#include "CEditorLevel.h"

#include "resource.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CLevelMgr.h"
#include "CPathMgr.h"

#include "CTexture.h"
#include "CTile.h"
#include "CUI.h"
#include "CButton.h"

CEditorLevel::CEditorLevel()	:
	m_hMenu(nullptr),
	m_eMode(EEDITOR_MODE::TILE)
{
}

CEditorLevel::~CEditorLevel()
{
	if(nullptr != m_hMenu)
		DestroyMenu(m_hMenu);
}

void CEditorLevel::Init()
{
	// 카메라 시점
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

	// UI 배치
	CUI* pButtonUI = new CButton;
	pButtonUI->SetScale(Vec2(100.f, 50.f));
	pButtonUI->SetPos(Vec2(vResolution.x - pButtonUI->GetScale().x - 10.f, 10.f));
	AddObj(pButtonUI, ELAYER::UI);

	// 타일이 사용할 아틀라스 이미지 설정
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");

	// 타일 생성
	CreateTile(8,6);

	// 각 타일에다가 사용할 아틀라스 이미지 및 인덱스 설정
	const vector<CObj*>& vecTile = GetLayer(ELAYER::TILE);	
	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->SetAtlas(pTex);
		((CTile*)vecTile[i])->SetImgIdx((int)i);
	}
}

void CEditorLevel::Tick()
{
	CLevel::Tick();

	if (IS_TAP(EKEY::ENTER))
	{
		ChangeLevel(ELEVEL_TYPE::START);
	}

	if (IS_TAP(EKEY::key1))
		m_eMode = EEDITOR_MODE::TILE;
	if (IS_TAP(EKEY::key2))
		m_eMode = EEDITOR_MODE::ANIMATINON;
	if (IS_TAP(EKEY::key3))
		m_eMode = EEDITOR_MODE::OBJECT;
	if (IS_TAP(EKEY::key0))
		m_eMode = EEDITOR_MODE::NONE;

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
	switch (m_eMode)
	{
	case EEDITOR_MODE::TILE:
		Tile_Update();
		break;
	case EEDITOR_MODE::ANIMATINON:

		break;
	case EEDITOR_MODE::OBJECT:

		break;
	case EEDITOR_MODE::NONE:
		return;
	}
}

void CEditorLevel::Tile_Update()
{
	if (IS_TAP(EKEY::LBTN))
	{
		// 마우스 위치를 받아서 실제좌표로 변환
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (0.f <= vMousePos.x && (int)GetTileXCount() > iCol &&
			0.f <= vMousePos.y && (int)GetTileYCount() > iRow)
		{
			int iIdx = iRow * GetTileXCount() + iCol;

			const vector<CObj*>& vecTile = GetLayer(ELAYER::TILE);
			((CTile*)vecTile[iIdx])->AddImgIdx();
		}
	}

	if (IS_TAP(EKEY::key8))
		SaveTile();

	if (IS_TAP(EKEY::key9))
		LoadTile();
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