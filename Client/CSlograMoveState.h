#pragma once
#include "CMonsterState.h"

class CSlograMoveState :
    public CMonsterState
{
public:
    CLONE(CSlograMoveState);

public:
    CSlograMoveState();
    ~CSlograMoveState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

