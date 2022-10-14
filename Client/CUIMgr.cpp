#include "pch.h"
#include "CUIMgr.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CUI.h"

CUIMgr::CUIMgr()	:
	m_pFocusedUI(nullptr),
	m_pPriorityUI(nullptr)
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

	for (int i = (int)vecUI.size() - 1; 0 <= i; i--)
	{
		m_pPriorityUI = GetPriorityUI((CUI*)vecUI[i]);

		if (nullptr == m_pPriorityUI)
			continue;

		// ���콺 �� �̺�Ʈ ȣ��
		m_pPriorityUI->MouseOn();

		// Lbtn�� �������ٸ� UI ���¸� ���������� �ٲ۴�
		if (bLbtDown)
		{
			m_pPriorityUI->MouseLbtnDown();

			m_pFocusedUI = (CUI*)vecUI[i];
			pCurLevel->SetFocusedUI(m_pFocusedUI);
			break;
		}

		// Lbtn�� ������ UI�� ������ �־��ٸ� Ŭ�� �̺�Ʈ ȣ��
		else if (bLbtReleased && m_pPriorityUI->m_bLbtnDown)
		{
			m_pPriorityUI->MouseLbtnClicked();
			m_pPriorityUI->m_bLbtnDown = false;
		}
	}
}

CUI* CUIMgr::GetPriorityUI(CUI* _pParentUi)
{
	bool bLbtReleased = IS_RELEASED(EKEY::LBTN);

	CUI* pPriorityUI = nullptr;

	static list<CUI*> queue;
	queue.clear();
	queue.push_back(_pParentUi);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		const vector<CUI*>& vecChildUI = pUI->GetChildUI();

		for (size_t i = 0; i < vecChildUI.size(); i++)
		{
			queue.push_back(vecChildUI[i]);
		}

		// UI ���� Ȯ��
		if (pUI->IsMouseOn())
		{	
			if (bLbtReleased && nullptr != pPriorityUI && pPriorityUI->IsLbtnDown())
				pPriorityUI->m_bLbtnDown = false;

			pPriorityUI = pUI;
		}
		else if(bLbtReleased)
			pUI->m_bLbtnDown = false;
	}

	return pPriorityUI;
}
