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
	m_eSpawnObjectOption(ESPAWNABLE_OBJECT::PLAYER),
	m_bFaceDir(true),
	m_eTriggerType(ETRIGGER_TYPE::LEVEL_CHANGE),
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
	// �޴��� ����
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

void CEditorLevel::SaveTile()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"tile\\";

	// Ž����� ������ ��ġ�� ��� ���� ����
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// ���� ���͸� ������ �� �ִ�
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	// ���ʿ� ������ ���� ������ �ε���
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// Ž���� â�� ���ʿ� ������ ���, null�� �ϸ� ���� �ֱٿ� ������ ��θ� �����ش�
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");

	if (nullptr != pFile)
	{
		// Ÿ�� ���� ���� ���� ����
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

	// Ž����� ������ ��ġ�� ��� ���� ����
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// ���� ���͸� ������ �� �ִ�
	ofn.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	// ���ʿ� ������ ���� ������ �ε���
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// Ž���� â�� ���ʿ� ������ ���, null�� �ϸ� ���� �ֱٿ� ������ ��θ� �����ش�
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetOpenFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"rb");
	
	if (nullptr != pFile)
	{
		// Ÿ�� ���� ���� �ҷ����� Ÿ�� ����
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

	// Ž����� ������ ��ġ�� ��� ���� ����
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// ���� ���͸� ������ �� �ִ�
	ofn.lpstrFilter = L"Level\0*.level\0ALL\0*.*";
	// ���ʿ� ������ ���� ������ �ε���
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// Ž���� â�� ���ʿ� ������ ���, null�� �ϸ� ���� �ֱٿ� ������ ��θ� �����ش�
	ofn.lpstrInitialDir = strTileFolderPath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (false == GetSaveFileName(&ofn))
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, szFilePath, L"wb");

	if (nullptr != pFile)
	{
		// �� ���� �κ�
		SaveBackGround(pFile);
		SaveForeGround(pFile);
		SavePlatform(pFile);
		SaveLine(pFile);

		SaveSpawnPoint(pFile);

		fclose(pFile);
	}
}

void CEditorLevel::LoadLevel()
{
	// open a file name
	OPENFILENAME ofn = {};

	wstring strTileFolderPath = CPathMgr::GetInst()->GetContentPath();
	strTileFolderPath += L"level\\";

	// Ž����� ������ ��ġ�� ��� ���� ����
	wchar_t szFilePath[256] = {};

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 256;
	// ���� ���͸� ������ �� �ִ�
	ofn.lpstrFilter = L"Level\0*.level\0ALL\0*.*";
	// ���ʿ� ������ ���� ������ �ε���
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	// Ž���� â�� ���ʿ� ������ ���, null�� �ϸ� ���� �ֱٿ� ������ ��θ� �����ش�
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

		// �ҷ��� ���Ͽ� �´� Ÿ�� �׸��带 ������ �ٽ� ������ �����ϴ�
		const vector<CObj*> vecForeGround = GetLayer(ELAYER::FOREGROUND);
		CBackGround* pForeGround = (CBackGround*)vecForeGround[0];
		const CTexture* pForeGroundImg = pForeGround->GetTex();

		if (nullptr != pForeGroundImg)
		{
			// �ε��� �̹����� ����� �°� �׸��� Ÿ���� ��ġ
			float iRow = round(pForeGroundImg->GetWidth() / (float)TILE_SIZE);
			float iCol = round(pForeGroundImg->GetHeight() / (float)TILE_SIZE);
			CreateTile((UINT)iRow, (UINT)iCol);
		}

		LoadPlatform(pFile);
		LoadLine(pFile);

		LoadSpawnPoint(pFile);

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
			// edit control���� �Էµ� ���� �޾ƿ���
			int iTileXCount =  GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int iTileYCount =  GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);

			if (!(iTileXCount && iTileYCount))
			{
				MessageBox(nullptr, L"Ÿ�� ������ �����ϼ���.", L"Ÿ�� ���� ����", MB_OK);
				return (INT_PTR)TRUE;
			}

			// ������ ���ڷ� Ÿ���� ���� �����Ѵ�
			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			pCurLevel->CreateTile(iTileXCount, iTileYCount);

			// �� Ÿ�Ͽ��ٰ� ����� ��Ʋ�� �̹��� �� �ε��� ����
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


// ======================
// Map Edit Dialog Proc
// ======================

wchar_t g_arrEditorMode[(UINT)EEDITOR_MODE::NONE][10] =
{
	L"Map",
	L"Object"
};

wchar_t g_arrFloorOption[(UINT)EFLOOR_OPTION::NONE][10] =
{
	L"Floor",
	L"Platform",
	L"Up Line",
	L"Down Line"
};

wchar_t g_arrObjOption[(UINT)EOBJ_OPTION::NONE][20] =
{
	L"Spawn Point",
	L"Object",
	L"Trigger"
};

wchar_t g_arrSpawnPointOption[(UINT)ESPAWNABLE_OBJECT::NONE][20] =
{
	L"Player",
	L"Bone Scimitar",
	L"Axe Armor",
	L"Skeleton",
	L"Spittle Bone",
	L"Gaibon",
	L"Slogra"
};

wchar_t g_arrFaceDir[2][10] =
{
	L"Left",
	L"Right"
};

wchar_t g_arrTriggerType[(UINT)ETRIGGER_TYPE::NONE][20] =
{
	L"Level Change"
};

INT_PTR CALLBACK LevelEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());

	if (nullptr == pEditorLevel)
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
		//CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());
		//assert(pEditorLevel);
		int iIdx = 0;

		// ������ ��� �޺��ڽ� �ʱ�ȭ
		HWND hWnd = GetDlgItem(hDlg, IDC_EDITOR_MODE);
		for (int i = 0; i < (UINT)EEDITOR_MODE::NONE; i++)
		{
			SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)g_arrEditorMode[i]);
		}
		iIdx = (int)pEditorLevel->GetEditorMode();
		SendMessage(hWnd, CB_SETCURSEL, iIdx, NULL);

		// �÷ξ� �ɼ� �޺��ڽ� �ʱ�ȭ
		hWnd = GetDlgItem(hDlg, IDC_FLOOR_OPTION);
		for (int i = 0; i < (UINT)EFLOOR_OPTION::NONE; i++)
		{
			SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)g_arrFloorOption[i]);
		}
		iIdx = (int)pEditorLevel->GetFloorOption();
		SendMessage(hWnd, CB_SETCURSEL, iIdx, NULL);

		// ������Ʈ �ɼ� �޺��ڽ� �ʱ�ȭ
		hWnd = GetDlgItem(hDlg, IDC_OBJECT_OPTION);
		for (int i = 0; i < (UINT)EOBJ_OPTION::NONE; i++)
		{
			SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)g_arrObjOption[i]);
		}
		iIdx = (int)pEditorLevel->GetObjOption();
		SendMessage(hWnd, CB_SETCURSEL, iIdx, NULL);

		// ���� ����Ʈ �ɼ� �޺��ڽ� �ʱ�ȭ
		hWnd = GetDlgItem(hDlg, IDC_SPAWN_POINT);
		for (int i = 0; i < (UINT)ESPAWNABLE_OBJECT::NONE; i++)
		{
			SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)g_arrSpawnPointOption[i]);
		}
		iIdx = (int)pEditorLevel->GetSpawnObjectOption();
		SendMessage(hWnd, CB_SETCURSEL, iIdx, NULL);

		// ��ġ ���� �޺��ڽ� �ʱ�ȭ
		hWnd = GetDlgItem(hDlg, IDC_FACE_DIR);
		for (int i = 0; i < 2; i++)
		{
			SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)g_arrFaceDir[i]);
		}
		iIdx = 0;
		if (pEditorLevel->GetDir())
			iIdx = 1;
		SendMessage(hWnd, CB_SETCURSEL, iIdx, NULL);

		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDITOR_MODE:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				EEDITOR_MODE eMode = (EEDITOR_MODE)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				pEditorLevel->ChangeEditorMode(eMode);
			}
				break;
			}
			break;
		case IDC_FLOOR_OPTION:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				EFLOOR_OPTION eOption = (EFLOOR_OPTION)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				pEditorLevel->ChangeFloorOption(eOption);
			}
				break;
			}
			break;
		case IDC_OBJECT_OPTION:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				EOBJ_OPTION eOption = (EOBJ_OPTION)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				pEditorLevel->ChangeObjectOption(eOption);
			}
				break;
			}
			break;
		case IDC_SPAWN_POINT:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				ESPAWNABLE_OBJECT eOption = (ESPAWNABLE_OBJECT)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				pEditorLevel->ChangeSpawnObjectOption(eOption);
			}
				break;
			}
			break;
		case IDC_FACE_DIR:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				bool bFaceDir = (bool)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				pEditorLevel->ChangeDir(bFaceDir);
			}
				break;
			}
			break;
		case IDC_LOAD_BACKGROUND:
			pEditorLevel->SetBackGroundImg();
			break;
		case IDC_LOAD_FOREGROUND:
			pEditorLevel->SetForeGroundImg();
			break;
		case IDC_SAVE_LEVEL:
			pEditorLevel->SaveLevel();
			break;
		case IDC_LOAD_LEVEL:
			pEditorLevel->LoadLevel();
			break;
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