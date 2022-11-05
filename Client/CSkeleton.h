#pragma once
#include "CMonster.h"

class CSkeleton :
    public CMonster
{
public:
    CLONE(CSkeleton);

public:
    CSkeleton();
    ~CSkeleton();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void Idle() override;
    virtual void Walk() override;
    virtual void Turn() override;
    virtual void Attack() override;

    virtual void Dead() override;
};

