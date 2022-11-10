#pragma once
#include "CMonsterState.h"

class CGaibonChangeState :
    public CMonsterState
{
public:
    CLONE(CGaibonChangeState);

public:
    CGaibonChangeState();
    ~CGaibonChangeState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

