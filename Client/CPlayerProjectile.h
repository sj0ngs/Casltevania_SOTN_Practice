#pragma once
#include "CProjectile.h"

class CPlayerProjectile :
    public CProjectile
{
public:
    CLONE_DEACTIVATE(CPlayerProjectile);

public:
    CPlayerProjectile();
    ~CPlayerProjectile();

public:
    virtual void Render(HDC _DC) override {};

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;
};

