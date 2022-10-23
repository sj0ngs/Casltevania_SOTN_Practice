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
	switch (m_eMapMode)
	{
	case EMAP_MODE::SOLID_PLATFORM:
	case EMAP_MODE::NON_SOLID_PLATFORM:
		EditPlatform();
		break;
	case EMAP_MODE::UP_LINE:
	case EMAP_MODE::DOWN_LINE:
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

					if (EMAP_MODE::NON_SOLID_PLATFORM == m_eMapMode)
						pPlatform->SetType(EPLATFORM_TYPE::NON_SOLID);

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

					if (EMAP_MODE::DOWN_LINE == m_eMapMode)
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

void CEditorLevel::LoadBackGround()
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
	size_t start = strFilePath.length() - 1;
	wstring Buff = szFilePath;
	size_t end = Buff.length();
	wstring FilePath = Buff.substr(start, end);

	CTexture* pBackGroundImg = CResMgr::GetInst()->LoadTexture(L"BackGroundImg", FilePath);

	// 로드한 이미지의 사이즈에 맞게 그리드 타일을 배치
	float iRow = round(pBackGroundImg->GetWidth() / (float)TILE_SIZE);
	float iCol = round(pBackGroundImg->GetHeight() / (float)TILE_SIZE);
	CreateTile((UINT)iRow, (UINT)iCol);

	CBackGround* pBackGround = new CBackGround;
	pBackGround->SetBackGroundImg(pBackGroundImg);
	pBackGround->SetIsForeGround(true);

	DeleteObject(ELAYER::BACKGROUND);
	AddObj(pBackGround, ELAYER::BACKGROUND);
}






// ======================
// Map Edit Dialog Proc
// ======================

struct tSelectMode
{
	wchar_t ModeName[10];
	EMAP_MODE eMode;
};

tSelectMode g_MapSelectMode[4] = {
	{L"Wall", EMAP_MODE::SOLID_PLATFORM},
	{L"Platform", EMAP_MODE::NON_SOLID_PLATFORM},
	{L"Up Line", EMAP_MODE::UP_LINE},
	{L"Down Line", EMAP_MODE::DOWN_LINE},
};

INT_PTR CALLBACK MapEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		HWND hWndSelectMode = GetDlgItem(hDlg, IDC_SELECT_MODE);
		for (int i = 0; i < 4; i++)
		{
			SendMessage(hWndSelectMode, CB_INSERTSTRING, -1, (LPARAM)g_MapSelectMode[i].ModeName);
		}
		SendMessageW(hWndSelectMode, CB_SETCURSEL, 0, NULL);
		return (INT_PTR)TRUE;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_SELECT_MODE:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				EMAP_MODE eMode = (EMAP_MODE)SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				CEditorLevel* pEditorLevel = dynamic_cast<CEditorLevel*>(CLevelMgr::GetInst()->GetCurLevel());

				if (nullptr != pEditorLevel)
				{
					pEditorLevel->ChangeMapMode(eMode);
				}
			}
			break;
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