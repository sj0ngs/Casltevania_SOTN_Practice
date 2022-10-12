#include "pch.h"
#include "CUIMgr.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CUI.h"

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Tick()
{
	bool bLbtDown = IS_TAP(EKEY::LBTN);
	bool bLbtReleased = IS_RELEASED(EKEY::LBTN);

	// 현재 레벨 접근
	// UI layer 가져오기
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	const vector<CObj*>& vecUI = pCurLevel->GetLayer(ELAYER::UI);

	for (size_t i = 0; i < vecUI.size(); i++)
	{
		CUI* pUI = (CUI*)vecUI[i];

		// UI 위에 마우스가 올라와 있다
		if (pUI->IsMouseOn())
		{
			// 마우스 온 이벤트 호출
			pUI->MouseOn();

			// Lbtn이 눌러졌다면 UI 상태를 눌러짐으로 바꾼다
			if (bLbtDown)
				pUI->MouseLbtnDown();
			// Lbtn이 때졌고 UI가 눌러져 있었다면 클릭 이벤트 호출
			if (bLbtReleased && pUI->m_bLbtnDown)
				pUI->MouseLbtnClicked();
		}
		// 안 올라와 있으면 다운 초기화
		if(bLbtReleased)
			pUI->m_bLbtnDown = false;
	}
}