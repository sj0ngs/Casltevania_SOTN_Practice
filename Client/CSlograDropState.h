#pragma once
#include "CMonsterState.h"

class CSlograDropState :
    public CMonsterState
{
private:
    float m_faccGroundTime;

    bool m_bIsGround;
    bool m_bColliderChanged;

public:
    CLONE(CSlograDropState);

public:
    CSlograDropState();
    ~CSlograDropState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

