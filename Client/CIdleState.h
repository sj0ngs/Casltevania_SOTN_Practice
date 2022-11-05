#pragma once
#include "CMonsterState.h"

class CIdleState :
    public CMonsterState
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

