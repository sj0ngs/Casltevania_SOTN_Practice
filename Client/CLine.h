#pragma once
#include "CObj.h"

enum class ELINE_TYPE : UINT8
{
	UP,
	DOWN
};

class CLine :
	public CObj
{
private:
	Vec2 m_vPos1;	// ¿ÞÂÊ ÁÂÇ¥
	Vec2 m_vPos2;	// ¿À¸¥ÂÊ ÁÂÇ¥
	ELINE_TYPE m_eType;
	tLine m_tLine;

	int m_iOverlapCount;

public:
	void SetPos1(Vec2 _vPos1) { m_vPos1 = _vPos1; };
	Vec2 GetPos1() const { return m_vPos1; }
	void SetPos2(Vec2 _vPos2) { m_vPos2 = _vPos2; };
	Vec2 GetPos2() const { return m_vPos2; }
	ELINE_TYPE GetType() const { return m_eType; }
	tLine& GetLine() { return m_tLine; }

public:
	CLONE(CLine);

public:
	CLine();
	CLine(const CLine& _Other);
	~CLine();

public:
	virtual void Tick() override;
	virtual void Render(HDC _DC)   override;

public:
	void BeginOverlap(CObj* _pOther);
	void OnOverlap(CObj* _pOther);
	void EndOverlap(CObj* _pOther);
};

