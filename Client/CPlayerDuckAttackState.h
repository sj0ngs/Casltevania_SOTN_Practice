#pragma once
#include "CPlayerAttackState.h"

class CPlayerDuckAttackState :
    public CPlayerAttackState
{
public:
    CLONE(CPlayerDuckAttackState);

public:
    CPlayerDuckAttackState();
    ~CPlayerDuckAttackState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
};

