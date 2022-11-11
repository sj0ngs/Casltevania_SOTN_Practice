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
	m_eSpawnObjectOption(ESPAWNABLE_OBJECT::BONE_SCIMITAR),
	m_bFaceDir(true),
	m_eTriggerType(ETRIGGER_TYPE::LEVEL_CHANGE),
	m_eChangeLevelType(ELEVEL_TYPE::START),
	m_vMousePos1{-1.f, -1.f}
{
}

CEditorLevel::~CEditorLevel()
{
	if(nullptr != m_hMenu)
		DestroyMenu(m_hMenu);
}

void CEditorLevel::Init()
{
	// ī�޶� ����
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);
}

void CEditorLevel::CreateUI(Vec2 _vResolution)
{
	// UI Texture �ε�
	//CTexture* pButtonTex = CResMgr::GetInst()->LoadTexture(L"Button", L"texture\\button.bmp");
	//CTexture* pButtonPressedTex = CResMgr::GetInst()->LoadTexture(L"Button_Pressed", L"texture\\button_pressed.bmp");
	//CTexture* pPanelTex = CResMgr::GetInst()->LoadTexture(L"Panel", L"texture\\OakUI.bmp");

	// UI ��ġ

	// �θ� �г� UI
	//CPanel* pPanel = new CPanel;
	//pPanel->SetIdleTex(pPanelTex);
	//pPanel->SetPos(Vec2(_vResolution.x - (pPanelTex->GetWidth() + 20.f), 10.f));

	// Back Ground Load Button
	//CButton* pLoadBackGround = pSaveTileButton->Clone();
	//pLoadBackGround->SetPos(Vec2(120.f, 160.f));
	//pLoadBackGround->SetDelegate(this, (DELEGATE)&CEditorLevel::SetBackGroundImg);

	// �гο� ��ư�� �ڽ����� �־��ش�
	//pPanel->AddChildUI(pLoadBackGround);
	//AddObj(pPanel, ELAYER::UI);

	//CUI* pOtherPanel = pPanel->Clone();
	//AddObj(pOtherPanel, ELAYER::UI);
}

void CEditorLevel::Tick()
{
	CLevel::Tick();

	if (CEngine::GetInst()->GetMainWnd() == GetForegroundWindow())
	{
		if (IS_TAP(EKEY::TAB))
		{
			ChangeLevel(ELEVEL_TYPE::ANIMATION);
		}
		if (IS_TAP(EKEY::key1))
		{
			ChangeLevel(ELEVEL_TYPE::START);
		}

		Update();
	}
}

void CEditorLevel::Render(HDC _DC)
{
	CLevel::Render(_DC);

	Vec2 vPos = CEngine::GetInst()->GetResolution();
	vPos /= 2.f;

	wstring strName = L"Map Editor";
	TextOut(_DC, (int)vPos.x, 0, strName.c_str(), (int)strName.length());
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

	CCamera::GetInst()->SetCameraMove(true);
}

void CEditorLevel::Exit()
{
	HWND hWnd = CEngine::GetInst()->GetMainWnd();
	SetMenu(hWnd, nullptr);

	POINT ptResolution = CEngine::GetInst()->GetResolution();
	CEngine::GetInst()->ChangeWindowSize(ptResolution.x, ptResolution.y);

	CCamera::GetInst()->SetCameraMove(false);
}

void CEditorLevel::Update()
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

		SaveStartPoint(pFile);
		SaveSpawnPoint(pFile);
		SaveTrigger(pFile);

		fclose(pFile);
	}
}

void CEditorLevel::LoadLevel()
{
	DeleteAllObject();

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

		LoadStartPoint(pFile);
		LoadSpawnPoint(pFile);
		LoadTrigger(pFile);

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
	L"Start Point",
	L"Spawn Point",
	L"Object",
	L"Trigger"
};

wchar_t g_arrSpawnPointOption[(UINT)ESPAWNABLE_OBJECT::NONE][20] =
{
	L"Bone Scimitar",
	L"Axe Armor",
	L"Skeleton",
	L"Blood Skeleton",
	L"Spittle Bone",
	L"Gaibon",
	L"Slogra",

	L"Candle"
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

wchar_t g_arrChangeLevelType[(UINT)ELEVEL_TYPE::END][20] =
{
	L"START",
	L"STAGE_01",
	L"STAGE_02",
	L"STAGE_03",
	L"Boss",
	L"EDITOR",
};

INT_PTR CALLBACK LevelEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		if (nullptr == pEditorLevel)
		{
			DestroyWindow(hDlg);
			hDlg = nullptr;
			return (INT_PTR)FALSE;
		}

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

		// Ʈ���� �ɼ� �޺��ڽ� �ʱ�ȭ
		hWnd = GetDlgItem(hDlg, IDC_TRIGGER_OPTION);
		for (int i = 0; i < (UINT)ETRIGGER_TYPE::NONE; i++)
		{
			SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)g_arrTriggerType[i]);
		}
		iIdx = (int)pEditorLevel->GetTriggerType();
		SendMessage(hWnd, CB_SETCURSEL, iIdx, NULL);

		// ���� ü���� Ʈ���� �޺��ڽ� �ʱ�ȭ
		hWnd = GetDlgItem(hDlg, IDC_LEVEL_CHANGE_TRIGGER);
		for (int i = 0; i < (UINT)ELEVEL_TYPE::END; i++)
		{
			SendMessage(hWnd, CB_INSERTSTRING, -1, (LPARAM)g_arrChangeLevelType[i]);
		}
		iIdx = (int)pEditorLevel->GetChangeLevelType();
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
		case IDC_START_POINT_IDX:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
			{
				UINT iIdx = GetDlgItemInt(hDlg, IDC_START_POINT_IDX, nullptr, true);
				pEditorLevel->SetStartPointIdx(iIdx);
			}
			break;
			}
			break;
		case IDC_TRIGGER_OPTION:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				ETRIGGER_TYPE eOption = (ETRIGGER_TYPE)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				pEditorLevel->ChangeTriggerType(eOption);
			}
			break;
			}
			break;
		case IDC_LEVEL_CHANGE_TRIGGER:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				ELEVEL_TYPE eOption = (ELEVEL_TYPE)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				pEditorLevel->ChangeLevelType(eOption);
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