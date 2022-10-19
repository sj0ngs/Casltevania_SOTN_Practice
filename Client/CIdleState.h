#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
public:
    CLONE(CIdleState);

public:
    CIdleState();
    ~CIdleState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

