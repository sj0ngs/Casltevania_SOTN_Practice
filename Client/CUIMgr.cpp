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

	// ���� ���� ����
	// UI layer ��������
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	const vector<CObj*>& vecUI = pCurLevel->GetLayer(ELAYER::UI);

	for (size_t i = 0; i < vecUI.size(); i++)
	{
		CUI* pUI = (CUI*)vecUI[i];

		// UI ���� ���콺�� �ö�� �ִ�
		if (pUI->IsMouseOn())
		{
			// ���콺 �� �̺�Ʈ ȣ��
			pUI->MouseOn();

			// Lbtn�� �������ٸ� UI ���¸� ���������� �ٲ۴�
			if (bLbtDown)
				pUI->MouseLbtnDown();
			// Lbtn�� ������ UI�� ������ �־��ٸ� Ŭ�� �̺�Ʈ ȣ��
			if (bLbtReleased && pUI->m_bLbtnDown)
				pUI->MouseLbtnClicked();
		}
		// �� �ö�� ������ �ٿ� �ʱ�ȭ
		if(bLbtReleased)
			pUI->m_bLbtnDown = false;
	}
}