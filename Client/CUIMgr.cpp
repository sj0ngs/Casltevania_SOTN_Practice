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
		// ���� �θ� UI�� UI Ʈ���ȿ����� �켱���� UI �ҷ���
		m_pPriorityUI = GetPriorityUI((CUI*)vecUI[i]);
		// nullptr �� ��ȯ��ٸ� ���� �θ� UI���� ���콺�� �ö��� �������̹Ƿ� ���� �ݺ����� �ѱ�
		if (nullptr == m_pPriorityUI)
			continue;

		// ���콺 �� �̺�Ʈ ȣ��
		// �켱���� UI Ž������ �̹� ���콺 �� ���¸� üũ����⿡ �ٷ� ���콺 �� �̺�Ʈ�� ȣ����
		m_pPriorityUI->MouseOn();

		// �̹� �����ӿ� Lbtn�� �������ٸ� UI ���¸� ���������� �ٲ۴�
		if (bLbtDown)
		{
			m_pPriorityUI->MouseLbtnDown();
			// ���콺 ������ �����Ǹ� �ش� �θ� UI�� ��Ŀ�� UI�� �������ش�
			// ��Ŀ�� UI�� �������� ���� �������� �ǵ��� ���Ϳ��� �ε����� ���� ���������� �������ش�
			m_pFocusedUI = (CUI*)vecUI[i];
			pCurLevel->SetFocusedUI(m_pFocusedUI);
			break;
		}

		// �̹� �����ӿ� Lbtn�� ������ UI�� ������ ���¿��ٸ� Ŭ�� �̺�Ʈ ȣ��
		else if (bLbtReleased && m_pPriorityUI->m_bLbtnDown)
		{
			m_pPriorityUI->MouseLbtnClicked();
			m_pPriorityUI->m_bLbtnDown = false;
		}
	}
}

// UI Ʈ������ ���콺�� �ö� UI���� ���� ���� ��� UI�� ã�� 
// �켱���� UI�� ��ȯ�Ѵ�
CUI* CUIMgr::GetPriorityUI(CUI* _pParentUi)
{
	bool bLbtReleased = IS_RELEASED(EKEY::LBTN);
	// �ش� UIƮ���� ���콺�� �ö��� �ʾҴٸ� nullptr�� ��ȯ�ϰ� �ȴ�
	CUI* pPriorityUI = nullptr;
	// �ʺ� �켱 Ž���� ���ؼ� ���� ��� UI�� ���� ���߿� Ž���ǵ����Ѵ�
	static list<CUI*> queue;
	queue.clear();
	queue.push_back(_pParentUi);

	while (!queue.empty())
	{	
		// �ʺ� �켱 Ž�� ����
		CUI* pUI = queue.front();
		queue.pop_front();

		const vector<CUI*>& vecChildUI = pUI->GetChildUI();

		for (size_t i = 0; i < vecChildUI.size(); i++)
		{
			queue.push_back(vecChildUI[i]);
		}

		// UI ���� Ȯ��
		// ������ UI�� ���콺�� �ö��־��ٸ� �׳༮�� �켱���� UI�� �ȴ�
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
