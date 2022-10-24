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

	// ��׶��� �̹��� ����
	//CTexture* pBackGroundTex = CResMgr::GetInst()->LoadTexture(L"DebugRoom", L"texture\\Debug Room .bmp");
	//CBackGround* pBackGround = new CBackGround;
	//pBackGround->SetBackGroundImg(pBackGroundTex);
	//pBackGround->SetIsForeGround(true);

	//AddObj(pBackGround, ELAYER::BACKGROUND);

	//UI ��ġ
	CreateUI(vResolution);

	//// Ÿ�� ����
	//CreateTile(10, 10);
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
	pLoadTileButton->SetPos(Vec2(120.f, 120.f));
	pLoadTileButton->SetDelegate(this, (DELEGATE)&CEditorLevel::LoadTile);

	// Back Ground Load Button
	CButton* pLoadBackGround = pSaveTileButton->Clone();
	pLoadBackGround->SetPos(Vec2(120.f, 160.f));
	pLoadBackGround->SetDelegate(this, (DELEGATE)&CEditorLevel::SetBackGroundImg);

	// �гο� ��ư�� �ڽ����� �־��ش�
	pPanel->AddChildUI(pSaveTileButton);
	pPanel->AddChildUI(pLoadTileButton);
	pPanel->AddChildUI(pLoadBackGround);
	AddObj(pPanel, ELAYER::UI);

	//CUI* pOtherPanel = pPanel->Clone();
	//AddObj(pOtherPanel, ELAYER::UI);
}
