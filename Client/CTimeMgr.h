#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llFrequency;

	UINT m_iFPS;
	float m_fDeltaTime;
	float m_fTime;

public:
	float GetDeltaTime()
	{
		return m_fDeltaTime;
	}

	UINT GetFPS()
	{
		return m_iFPS;
	}

public:
	void Init();
	void Tick();
	void Render();
};

