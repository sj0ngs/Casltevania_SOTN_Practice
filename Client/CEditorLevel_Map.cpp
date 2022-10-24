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
#include "CLine.h"

#include "CCollider.h"
#include "CTexture.h"
#include "CTile.h"
#include "CUI.h"
#include "CButton.h"

void CEditorLevel::Map_Update()
{
	switch (m_eFloorOption)
	{
	case EFLOOR_OPTION::FLOOR:
	case EFLOOR_OPTION::PLATFORM:
		EditPlatform();
		break;
	case EFLOOR_OPTION::UP_LINE:
	case EFLOOR_OPTION::DOWN_LINE:
		EditLine();
		break;
	}
}

void CEditorLevel::EditPlatform()
{
	// 마우스 왼쪽 클릭으로 플랫폼 설치
	if (IS_TAP(EKEY::LBTN))
	{
		if (m_vMousePos1 == Vec2(-1.f, -1.f))
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
				m_vMousePos1 = vecTile[iIdx]->GetPos();
			}
		}
		else
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
				Vec2 vPos = vecTile[iIdx]->GetPos();
				vPos += Vec2((float)TILE_SIZE, (float)TILE_SIZE);

				if (m_vMousePos1.x > vPos.x)
				{
					float temp = m_vMousePos1.x;
					m_vMousePos1.x = vPos.x;
					vPos.x = temp;
					m_vMousePos1.x -= TILE_SIZE;
					vPos.x += TILE_SIZE;
				}
				if (m_vMousePos1.y > vPos.y)
				{
					float temp = m_vMousePos1.y;
					m_vMousePos1.y = vPos.y;
					vPos.y = temp;
					m_vMousePos1.y -= TILE_SIZE;
					vPos.y += TILE_SIZE;
				}
				if (m_vMousePos1.x < vPos.x && m_vMousePos1.y < vPos.y)
				{
					Vec2 vScale = vPos - m_vMousePos1;
					m_vMousePos1 += (vScale / 2.f);

					CPlatform* pPlatform = new CPlatform;
					pPlatform->GetCollider()->SetScale(vScale);
					pPlatform->SetPos(m_vMousePos1);

					if (EFLOOR_OPTION::PLATFORM == m_eFloorOption)
						pPlatform->SetType(EPLATFORM_TYPE::PLATFORM);

					AddObj(pPlatform, ELAYER::PLATFORM);
				}
			}
			m_vMousePos1 = Vec2(-1.f, -1.f);
		}
	}

	// 우클릭으로 플랫폼을 없앤다
	if (IS_TAP(EKEY::RBTN))
	{
		// 마우스 위치를 받아서 실제좌표로 변환
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		const vector<CObj*>& vecPlatform = GetLayer(ELAYER::PLATFORM);

		for (size_t i = 0; i < vecPlatform.size(); i++)
		{
			Vec2 vPos = vecPlatform[i]->GetPos();
			Vec2 vScale = vecPlatform[i]->GetCollider()->GetScale();
			vScale /= 2.f;

			if (vPos.x - vScale.x <= vMousePos.x && vPos.x + vScale.x >= vMousePos.x &&
				vPos.y - vScale.y <= vMousePos.y && vPos.y + vScale.y >= vMousePos.y)
			{
				vecPlatform[i]->SetDead();
				break;
			}
		}
	}
}

void CEditorLevel::EditLine()
{
	// 마우스 왼쪽 클릭으로 플랫폼 설치
	if (IS_TAP(EKEY::LBTN))
	{
		if (m_vMousePos1 == Vec2(-1.f, -1.f))
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
				m_vMousePos1 = vecTile[iIdx]->GetPos();
			}
		}
		else
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
				Vec2 vPos = vecTile[iIdx]->GetPos();

				if (m_vMousePos1.x > vPos.x)
				{
					Vec2 temp = m_vMousePos1;
					m_vMousePos1 = vPos;
					vPos = temp;
				}
				vPos.x += TILE_SIZE;

				if (m_vMousePos1.y > vPos.y)
					m_vMousePos1.y += TILE_SIZE;
				else if (m_vMousePos1.y < vPos.y)
					vPos.y += TILE_SIZE;

				if (m_vMousePos1.y != vPos.y)
				{
					CLine* pLine = new CLine;

					pLine->SetPos1(m_vMousePos1);
					pLine->SetPos2(vPos);

					if (EFLOOR_OPTION::DOWN_LINE == m_eFloorOption)
						pLine->SetType(ELINE_TYPE::DOWN);

					AddObj(pLine, ELAYER::LINE);
				}
			}
			m_vMousePos1 = Vec2(-1.f, -1.f);
		}
	}

	// 우클릭으로 플랫폼을 없앤다
	if (IS_TAP(EKEY::RBTN))
	{
		// 마우스 위치를 받아서 실제좌표로 변환
		Vec2 vMousePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

		const vector<CObj*>& vecLine = GetLayer(ELAYER::LINE);

		for (size_t i = 0; i < vecLine.size(); i++)
		{
			CLine* pLine = (CLine*)vecLine[i];
			Vec2 vPos1 = pLine->GetPos1();
			Vec2 vPos2 = pLine->GetPos2();

			if (vPos1.y > vPos2.y)
			{
				float temp = vPos1.y;
				vPos1.y = vPos2.y;
				vPos2.y = temp;
			}

			if (vPos1.x <= vMousePos.x && vPos2.x >= vMousePos.x &&
				vPos1.y <= vMousePos.y && vPos2.y >= vMousePos.y)
			{
				vecLine[i]->SetDead();
				break;
			}
		}
	}
}

void CEditorLevel::SetBackGroundImg()
{
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

	CTexture* pBackGroundImg = CResMgr::GetInst()->LoadTexture(strKey, FilePath);

	CBackGround* pBackGround = new CBackGround;
	pBackGround->SetBackGroundImg(pBackGroundImg);

	DeleteObject(ELAYER::BACKGROUND);
	AddObj(pBackGround, ELAYER::BACKGROUND);
}

void CEditorLevel::SetForeGroundImg()
{
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
	wstring FilePath = szFilePath;
	size_t end = FilePath.length();
	FilePath = FilePath.substr(start, end);

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

	CTexture* pForeGroundImg = CResMgr::GetInst()->LoadTexture(strKey, FilePath);

	// 로드한 이미지의 사이즈에 맞게 그리드 타일을 배치
	float iRow = round(pForeGroundImg->GetWidth() / (float)TILE_SIZE);
	float iCol = round(pForeGroundImg->GetHeight() / (float)TILE_SIZE);
	CreateTile((UINT)iRow, (UINT)iCol);

	CBackGround* pForeGround = new CBackGround;
	pForeGround->SetBackGroundImg(pForeGroundImg);
	pForeGround->SetIsForeGround(true);

	DeleteObject(ELAYER::FOREGROUND);
	AddObj(pForeGround, ELAYER::FOREGROUND);
}

void CEditorLevel::SaveBackGround(FILE* _pFile)
{
	const vector<CObj*>& vecBackGround = GetLayer(ELAYER::BACKGROUND);

	size_t iSize = vecBackGround.size();
	fwrite(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		vecBackGround[i]->Save(_pFile);
	}
}

void CEditorLevel::SaveForeGround(FILE* _pFile)
{
	const vector<CObj*>& vecForeGround = GetLayer(ELAYER::FOREGROUND);

	size_t iSize = vecForeGround.size();
	fwrite(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		vecForeGround[i]->Save(_pFile);
	}
}

void CEditorLevel::SavePlatform(FILE* _pFile)
{
	const vector<CObj*>& vecPlatform = GetLayer(ELAYER::PLATFORM);

	size_t iSize = vecPlatform.size();
	fwrite(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		vecPlatform[i]->Save(_pFile);
	}
}

void CEditorLevel::SaveLine(FILE* _pFile)
{
	const vector<CObj*>& vecLine = GetLayer(ELAYER::LINE);

	size_t iSize = vecLine.size();
	fwrite(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		vecLine[i]->Save(_pFile);
	}
}


// ================
// Level Load Funcs
// ================

// Load 함수들은 모든 레벨에서 사용해야 되기 때문에 최상위 Level 에 선언되어있다
// 하지만 편집의 편의성을 위하여 구현부는 에디터 레벨에다 작성한다
void CLevel::LoadBackGround(FILE* _pFile)
{
	size_t iSize;
	fread(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		CBackGround* pBackGround = new CBackGround;
		pBackGround->Load(_pFile);
		AddObj(pBackGround, ELAYER::BACKGROUND);
	}
}

void CLevel::LoadForeGround(FILE* _pFile)
{
	size_t iSize;
	fread(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		CBackGround* pForeGround = new CBackGround;
		pForeGround->Load(_pFile);
		AddObj(pForeGround, ELAYER::FOREGROUND);
	}
}

void CLevel::LoadPlatform(FILE* _pFile)
{
	size_t iSize;
	fread(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		CPlatform* pPlatform = new CPlatform;
		pPlatform->Load(_pFile);
		AddObj(pPlatform, ELAYER::PLATFORM);
	}
}

void CLevel::LoadLine(FILE* _pFile)
{
	size_t iSize;
	fread(&iSize, sizeof(size_t), 1, _pFile);

	for (size_t i = 0; i < iSize; i++)
	{
		CLine* pLine = new CLine;
		pLine->Load(_pFile);
		AddObj(pLine, ELAYER::LINE);
	}
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

INT_PTR CALLBACK MapEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		HWND hWndEditorMode = GetDlgItem(hDlg, IDC_EDITOR_MODE);

		for (int i = 0; i < (UINT)EEDITOR_MODE::NONE; i++)
		{
			SendMessage(hWndEditorMode, CB_INSERTSTRING, -1, (LPARAM)g_arrEditorMode[i]);
		}
		SendMessage(hWndEditorMode, CB_SETCURSEL, 0, NULL);

		HWND hWndFloorOption = GetDlgItem(hDlg, IDC_FLOOR_OPTION);
		
		for (int i = 0; i < (UINT)EFLOOR_OPTION::NONE; i++)
		{
			SendMessage(hWndFloorOption, CB_INSERTSTRING, -1, (LPARAM)g_arrFloorOption[i]);
		}
		SendMessage(hWndFloorOption, CB_SETCURSEL, 0, NULL);

		HWND hWndMapObjectOption = GetDlgItem(hDlg, IDC_OBJECT_OPTION);

		for (int i = 0; i < (UINT)EOBJ_OPTION::NONE; i++)
		{
			SendMessage(hWndMapObjectOption, CB_INSERTSTRING, -1, (LPARAM)g_arrObjOption[i]);
		}
		SendMessage(hWndMapObjectOption, CB_SETCURSEL, 0, NULL);

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
				CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());

				if (nullptr != pEditorLevel)
				{
					pEditorLevel->ChangeEditorMode(eMode);
				}
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
				CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());

				if (nullptr != pEditorLevel)
				{
					pEditorLevel->ChangeFloorOption(eOption);
				}
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
				CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());

				if (nullptr != pEditorLevel)
				{
					pEditorLevel->ChangeObjectOption(eOption);
				}
			}
				break;
			}
			break;
		case IDC_LOAD_BACKGROUND:
		{
			CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());
			assert(pEditorLevel);
			pEditorLevel->SetBackGroundImg();
		}
			break;
		case IDC_LOAD_FOREGROUND:
		{
			CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());
			assert(pEditorLevel);
			pEditorLevel->SetForeGroundImg();
		}
			break;
		case IDC_SAVE_LEVEL:
		{
			CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());
			assert(pEditorLevel);
			pEditorLevel->SaveLevel();
		}
			break;
		case IDC_LOAD_LEVEL:
		{
			CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());
			assert(pEditorLevel);
			pEditorLevel->LoadLevel();
		}
			break;
		case IDOK:
		case IDCANCEL:
			DestroyWindow(hDlg);
			hDlg = nullptr;
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}