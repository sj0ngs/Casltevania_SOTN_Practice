#pragma once
#include "CPlayerState.h"
class CPlayerJumpState :
    public CPlayerState
{
private:
    float m_accJumpTime;
public:
    CLONE(CPlayerJumpState);

public:
    CPlayerJumpState();
    ~CPlayerJumpState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

