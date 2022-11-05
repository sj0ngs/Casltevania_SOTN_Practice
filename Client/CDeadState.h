#pragma once
#include "CMonsterState.h"

class CDeadState :
    public CMonsterState
{
public:
    CLONE(CDeadState);

public:
    CDeadState();
    ~CDeadState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

