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

	// 현재 레벨 접근
	// UI layer 가져오기
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	const vector<CObj*>& vecUI = pCurLevel->GetLayer(ELAYER::UI);
	
	for (int i = (int)vecUI.size() - 1; 0 <= i; i--)
	{
		// 현재 부모 UI의 UI 트리안에서의 우선순위 UI 불러옴
		m_pPriorityUI = GetPriorityUI((CUI*)vecUI[i]);
		// nullptr 이 반환됬다면 현재 부모 UI에는 마우스가 올라가지 않은것이므로 다음 반복으로 넘김
		if (nullptr == m_pPriorityUI)
			continue;

		// 마우스 온 이벤트 호출
		// 우선순위 UI 탐색에서 이미 마우스 온 상태를 체크해줬기에 바로 마우스 온 이벤트를 호출함
		m_pPriorityUI->MouseOn();

		// 이번 프레임에 Lbtn이 눌러졌다면 UI 상태를 눌러짐으로 바꾼다
		if (bLbtDown)
		{
			m_pPriorityUI->MouseLbtnDown();
			// 마우스 누름이 감지되면 해당 부모 UI를 포커스 UI로 변경해준다
			// 포커스 UI는 랜더링이 가장 마지막에 되도록 벡터에서 인덱스를 가장 마지막으로 변경해준다
			m_pFocusedUI = (CUI*)vecUI[i];
			pCurLevel->SetFocusedUI(m_pFocusedUI);
			break;
		}

		// 이번 프레임에 Lbtn이 때졌고 UI가 눌러짐 상태였다면 클릭 이벤트 호출
		else if (bLbtReleased && m_pPriorityUI->m_bLbtnDown)
		{
			m_pPriorityUI->MouseLbtnClicked();
			m_pPriorityUI->m_bLbtnDown = false;
		}
	}
}

// UI 트리안의 마우스가 올라간 UI들중 가장 말단 노드 UI를 찾아 
// 우선순위 UI로 반환한다
CUI* CUIMgr::GetPriorityUI(CUI* _pParentUi)
{
	bool bLbtReleased = IS_RELEASED(EKEY::LBTN);
	// 해당 UI트리에 마우스가 올라가지 않았다면 nullptr을 반환하게 된다
	CUI* pPriorityUI = nullptr;
	// 너비 우선 탐색을 통해서 리프 노드 UI가 가장 나중에 탐색되도록한다
	static list<CUI*> queue;
	queue.clear();
	queue.push_back(_pParentUi);

	while (!queue.empty())
	{	
		// 너비 우선 탐색 진행
		CUI* pUI = queue.front();
		queue.pop_front();

		const vector<CUI*>& vecChildUI = pUI->GetChildUI();

		for (size_t i = 0; i < vecChildUI.size(); i++)
		{
			queue.push_back(vecChildUI[i]);
		}

		// UI 상태 확인
		// 꺼내온 UI에 마우스가 올라가있었다면 그녀석이 우선순위 UI가 된다
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
