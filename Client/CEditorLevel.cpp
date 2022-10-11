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
	// ī�޶� ����
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

	// Ÿ���� ����� ��Ʋ�� �̹��� ����
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");

	// Ÿ�� ����
	CreateTile(8,6);

	// �� Ÿ�Ͽ��ٰ� ����� ��Ʋ�� �̹��� �� �ε��� ����
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
			// �Էµ� ���� �޾ƿ���
			int iTileXCount =  GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, true);
			int iTileYCount =  GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, true);

			if (!(iTileXCount && iTileYCount))
			{
				MessageBox(nullptr, L"Ÿ�� ������ �����ϼ���.", L"Ÿ�� ���� ����", MB_OK);
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