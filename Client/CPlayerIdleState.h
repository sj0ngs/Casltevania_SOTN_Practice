#pragma once
#include "CPlayerState.h"

class CPlayerIdleState :
    public CPlayerState
{
public:
    CLONE(CPlayerIdleState);

public:
    CPlayerIdleState();
    ~CPlayerIdleState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

