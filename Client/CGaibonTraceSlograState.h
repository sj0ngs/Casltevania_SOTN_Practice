#pragma once
#include "CMonsterState.h"

class CGaibonTraceSlograState :
    public CMonsterState
{
public:
    CLONE(CGaibonTraceSlograState);

public:
    CGaibonTraceSlograState();
    ~CGaibonTraceSlograState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

