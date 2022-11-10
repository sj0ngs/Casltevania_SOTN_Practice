#pragma once
#include "CMonsterState.h"

class CGaibonStandByState :
    public CMonsterState
{
public:
    CLONE(CGaibonStandByState);

public:
    CGaibonStandByState();
    ~CGaibonStandByState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

