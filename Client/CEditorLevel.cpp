#include "pch.h"
#include "CEditorLevel.h"

#include "resource.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CLevelMgr.h"

#include "CTile.h"

CEditorLevel::CEditorLevel()
{
}

CEditorLevel::~CEditorLevel()
{
}

void CEditorLevel::Init()
{
	// 카메라 시점
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

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

	if (IS_TAP(EKEY::key0))
	{
		ChangeLevel(ELEVEL_TYPE::START);
	}
}

void CEditorLevel::Enter()
{
	Init();
}

void CEditorLevel::Exit()
{
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
			// 입력된 숫자 받아오기
			int iTileXCount =  GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int iTileYCount =  GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);

			if (!(iTileXCount && iTileYCount))
			{
				MessageBox(nullptr, L"타일 개수를 지정하세요.", L"타일 생성 오류", MB_OK);
				return (INT_PTR)TRUE;
			}

			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

			pCurLevel->CreateTile(iTileXCount, iTileYCount);

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