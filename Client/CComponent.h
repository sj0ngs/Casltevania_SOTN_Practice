#pragma once
#include "CEntity.h"

class CObj;
class CComponent	: 
	public CEntity
{
private:
	CObj* m_pOwner;

public:
	CObj* GetOwner() { return m_pOwner; }

private:
	void SetOwner(CObj* _pOwner) { m_pOwner = _pOwner; }

public:
	CComponent(CObj* _pOwner);
	~CComponent();

	friend class CObj;

public:
	virtual void Tick() = 0;
	virtual void Final_Tick() {};
	virtual void Render(HDC _DC) = 0;
};

