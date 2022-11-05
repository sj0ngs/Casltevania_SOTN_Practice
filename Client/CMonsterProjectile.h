#pragma once
#include "CProjectile.h"

class CMonsterProjectile :
    public CProjectile
{
public:
    CLONE_DEACTIVATE(CMonsterProjectile);

public:
    CMonsterProjectile();
    ~CMonsterProjectile();

public:
    virtual void Render(HDC _DC) override {};

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;
};

