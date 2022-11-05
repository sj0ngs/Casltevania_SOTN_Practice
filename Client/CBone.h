#pragma once
#include "CMonsterProjectile.h"

class CBone :
    public CMonsterProjectile
{
public:
    CLONE(CBone);

public:
    CBone();
    ~CBone();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;
};

