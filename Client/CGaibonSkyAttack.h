#pragma once
#include "CMonsterState.h"

class CGaibonSkyAttack :
    public CMonsterState
{
private:
    float m_fSkyAttackTime;
    float m_faccAttackTime;

    float m_faccFireTime;

    bool m_bAttackEnd;

public:
    CLONE(CGaibonSkyAttack);

public:
    CGaibonSkyAttack();
    ~CGaibonSkyAttack();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

