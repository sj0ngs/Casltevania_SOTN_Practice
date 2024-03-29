#pragma once
#include "CPlayerProjectile.h"

class CCover :
    public CPlayerProjectile
{
public:
    CLONE(CCover);

public:
    CCover();
    ~CCover();

public:
    virtual void Render(HDC _DC) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;
};

