#pragma once
#include "CMonsterState.h"

class CAttackState :
    public CMonsterState
{
public:
    CLONE(CAttackState);

public:
    CAttackState();
    ~CAttackState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

