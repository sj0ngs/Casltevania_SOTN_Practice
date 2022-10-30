#pragma once
#include "CPlayerState.h"
class CPlayerBackDashState :
    public CPlayerState
{
private:
    float m_faccDashTime;
    float m_fDashSpeed;

public:
    CLONE(CPlayerBackDashState);

public:
    CPlayerBackDashState();
    ~CPlayerBackDashState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

