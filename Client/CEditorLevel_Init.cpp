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

	CResMgr::GetInst()->LoadTexture(L"alucard_right_1", L"texture\\alucard_right_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"alucard_left_1", L"texture\\alucard_left_1.bmp");
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
