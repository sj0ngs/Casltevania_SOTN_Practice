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
	// 카메라 시점
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CCamera::GetInst()->SetLook(vResolution / 2.f);

	CResMgr::GetInst()->LoadTexture(L"alucard_right_1", L"texture\\alucard_right_1.bmp");
	CResMgr::GetInst()->LoadTexture(L"alucard_left_1", L"texture\\alucard_left_1.bmp");
}

void CEditorLevel::CreateUI(Vec2 _vResolution)
{
	// UI Texture 로드
	//CTexture* pButtonTex = CResMgr::GetInst()->LoadTexture(L"Button", L"texture\\button.bmp");
	//CTexture* pButtonPressedTex = CResMgr::GetInst()->LoadTexture(L"Button_Pressed", L"texture\\button_pressed.bmp");
	//CTexture* pPanelTex = CResMgr::GetInst()->LoadTexture(L"Panel", L"texture\\OakUI.bmp");

	// UI 배치

	// 부모 패널 UI
	//CPanel* pPanel = new CPanel;
	//pPanel->SetIdleTex(pPanelTex);
	//pPanel->SetPos(Vec2(_vResolution.x - (pPanelTex->GetWidth() + 20.f), 10.f));

	// Back Ground Load Button
	//CButton* pLoadBackGround = pSaveTileButton->Clone();
	//pLoadBackGround->SetPos(Vec2(120.f, 160.f));
	//pLoadBackGround->SetDelegate(this, (DELEGATE)&CEditorLevel::SetBackGroundImg);

	// 패널에 버튼을 자식으로 넣어준다
	//pPanel->AddChildUI(pLoadBackGround);
	//AddObj(pPanel, ELAYER::UI);

	//CUI* pOtherPanel = pPanel->Clone();
	//AddObj(pOtherPanel, ELAYER::UI);
}
