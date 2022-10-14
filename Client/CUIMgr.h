#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	CUI* m_pFocusedUI;
	CUI* m_pPriorityUI;

public:
	void Tick();

public:
	// 최상위 부모 ui 포함, 자식 ui 까지 포함해서 우선순위를 계산한다
	CUI* GetPriorityUI(CUI* _pParentUi);
};

