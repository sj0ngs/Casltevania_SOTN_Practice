#pragma once

class CLevel;
class CObj;

class CLevelMgr
{
	SINGLE(CLevelMgr);

private:
	CLevel* m_arrLevel[(UINT)ELEVEL_TYPE::END];
	CLevel* m_pCurLevel;

public:
	void Init();
	void Tick();
	void Render(HDC _DC);

private:
	void ChangeLevel(ELEVEL_TYPE _eNext);

public:
	CLevel* GetCurLevel()
	{
		return m_pCurLevel;
	}

	CLevel* GetLevel(ELEVEL_TYPE _eType);

	friend class CEventMgr;
};

