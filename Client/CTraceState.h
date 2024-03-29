#pragma once
#include "CMonsterState.h"

class CTraceState :
    public CMonsterState
{
private:
    bool m_bCanAttack;
    float m_faccAttackCool;

public:
    CLONE(CTraceState);

public:
    CTraceState();
    ~CTraceState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

