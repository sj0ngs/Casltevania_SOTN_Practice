#pragma once
#include "CMonsterState.h"

class CTraceState :
    public CMonsterState
{
public:
    CTraceState();
    ~CTraceState();

public:
    CLONE(CTraceState);

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

