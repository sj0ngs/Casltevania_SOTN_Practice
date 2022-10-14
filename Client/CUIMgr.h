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
	// �ֻ��� �θ� ui ����, �ڽ� ui ���� �����ؼ� �켱������ ����Ѵ�
	CUI* GetPriorityUI(CUI* _pParentUi);
};

