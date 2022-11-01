#pragma once
#include "CPlayerAttackState.h"

class CPlayerStandAttackState :
    public CPlayerAttackState
{
public:
    CLONE(CPlayerStandAttackState);

public:
    CPlayerStandAttackState();
    ~CPlayerStandAttackState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
};

