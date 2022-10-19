#pragma once
#include "CState.h"
class CTraceState :
    public CState
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

