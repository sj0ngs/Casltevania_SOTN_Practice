#pragma once
#include "CMonsterState.h"

class CSlograStandBy :
    public CMonsterState
{
public:
    CLONE(CSlograStandBy);

public:
    CSlograStandBy();
    ~CSlograStandBy();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

