#pragma once
#include "CMonsterState.h"

class CSlograIdleState :
    public CMonsterState
{
private:
    float m_fStopTime;
    float m_faccStopTime;

public:
    CLONE(CSlograIdleState);

public:
    CSlograIdleState();
    ~CSlograIdleState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

