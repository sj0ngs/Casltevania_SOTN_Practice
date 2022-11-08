#pragma once
#include "CMonsterState.h"

class CSlograAttackState :
    public CMonsterState
{
public:
    CLONE(CSlograAttackState);

public:
    CSlograAttackState();
    ~CSlograAttackState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

