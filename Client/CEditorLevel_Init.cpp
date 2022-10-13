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
#include "CPanel.h"

void CEditorLevel::Init()
{
	// ī�޶� ����
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

	//UI ��ġ
	CreateUI(vResolution);

	// Ÿ���� ����� ��Ʋ�� �̹��� ����
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"TileAtlas", L"texture\\TILE.bmp");

	// Ÿ�� ����
	CreateTile(8, 6);

	// �� Ÿ�Ͽ��ٰ� ����� ��Ʋ�� �̹��� �� �ε��� ����
	const vector<CObj*>& vecTile = GetLayer(ELAYER::TILE);
	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->SetAtlas(pTex);
		((CTile*)vecTile[i])->SetImgIdx((int)i);
	}
}

void CEditorLevel::CreateUI(Vec2 _vResolution)
{
	// UI Texture �ε�
	CTexture* pButtonTex = CResMgr::GetInst()->LoadTexture(L"Button", L"texture\\button.bmp");
	CTexture* pButtonPressedTex = CResMgr::GetInst()->LoadTexture(L"Button_Pressed", L"texture\\button_pressed.bmp");
	CTexture* pPanelTex = CResMgr::GetInst()->LoadTexture(L"Panel", L"texture\\OakUI.bmp");

	// UI ��ġ

	// �θ� �г� UI
	CPanel* pPanel = new CPanel;
	pPanel->SetIdleTex(pPanelTex);
	pPanel->SetPos(Vec2(_vResolution.x - (pPanelTex->GetWidth() + 20.f), 10.f));

	// Save Button
	CButton* pSaveTileButton = new CButton;
	pSaveTileButton->SetPos(Vec2(120.f, 80.f));
	pSaveTileButton->SetDelegate(this, (DELEGATE)&CEditorLevel::SaveTile);
	pSaveTileButton->SetIdleTex(pButtonTex);
	pSaveTileButton->SetPressTex(pButtonPressedTex);

	// Load Button
	CButton* pLoadTileButton = pSaveTileButton->Clone();
	pLoadTileButton->SetPos(Vec2(120.f, 160.f));
	pLoadTileButton->SetDelegate(this, (DELEGATE)&CEditorLevel::LoadTile);

	// �гο� ��ư�� �ڽ����� �־��ش�
	pPanel->AddChildUI(pSaveTileButton);
	pPanel->AddChildUI(pLoadTileButton);
	AddObj(pPanel, ELAYER::UI);
}