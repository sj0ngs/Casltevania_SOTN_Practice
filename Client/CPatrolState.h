#pragma once
#include "CMonsterState.h"

class CPatrolState :
    public CMonsterState
{
public:
    float m_faccTime;

public:
    CLONE(CPatrolState);

public:
    CPatrolState();
    ~CPatrolState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

