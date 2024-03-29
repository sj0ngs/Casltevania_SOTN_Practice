#pragma once
#include "CMonsterState.h"

class CSlograFireState :
    public CMonsterState
{
private:
    bool m_bFireEnd;
    float m_faccFireTime;

public:
    CLONE(CSlograFireState);

public:
    CSlograFireState();
    ~CSlograFireState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

