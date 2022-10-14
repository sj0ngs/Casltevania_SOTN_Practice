#pragma once
#include "CObj.h"

class CDiagonal :
	public CObj
{
public:
	CLONE(CDiagonal);

public:
	CDiagonal();
	~CDiagonal();

public:
	virtual void BeginOverlap(CCollider* _pOther)	override;
	virtual void OnOverlap(CCollider* _pOther)	override;
	virtual void EndOverlap(CCollider* _pOther)	override;
};

