#pragma once
#include "CMonsterState.h"

const float SLOGRA_HIT_TIME = 2.f;

class CSlograHitState :
    public CMonsterState
{
private:
    float m_faccHitTime;

public:
    CLONE(CSlograHitState);

public:
    CSlograHitState();
    ~CSlograHitState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

