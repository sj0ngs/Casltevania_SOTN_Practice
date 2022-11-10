#pragma once
#include "CMonsterState.h"

class CGaibonLandAttackState :
    public CMonsterState
{
private:
    float m_fLandAttackTime;
    float m_faccAttackTime;

    float m_faccFireTime;

public:
    CLONE(CGaibonLandAttackState);

public:
    CGaibonLandAttackState();
    ~CGaibonLandAttackState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

