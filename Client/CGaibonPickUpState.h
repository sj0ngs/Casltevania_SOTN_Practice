#pragma once
#include "CMonsterState.h"

class CGaibonPickUpState :
    public CMonsterState
{
private:
    float m_faccPickUpTime;

public:
    CLONE(CGaibonPickUpState);

public:
    CGaibonPickUpState();
    ~CGaibonPickUpState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

