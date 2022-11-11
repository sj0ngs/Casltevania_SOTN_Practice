#pragma once
#include "CObj.h"

class CCandle :
    public CObj
{
public:
    CLONE(CCandle);

public:
    CCandle();
    ~CCandle();

public:
    virtual void BeginOverlap(CCollider* _pOther) override;

    void DropItem();

    void DropHeart();
    void DropSubWeapon();
};

