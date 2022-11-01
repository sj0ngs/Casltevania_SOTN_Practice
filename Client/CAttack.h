#pragma once
#include "CObj.h"

class CAttack :
    public CObj
{
private:
    CObj* m_pOwner;

public:
    CLONE(CAttack);

public:
    CAttack(CObj* _pOwner);
    ~CAttack();

public:
    virtual void Render(HDC _DC) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;
};

