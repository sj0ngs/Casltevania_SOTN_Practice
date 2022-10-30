#pragma once
#include "CPlayerState.h"
class CPlayerLandingState :
    public CPlayerState
{
public:
    CLONE(CPlayerLandingState);

public:
    CPlayerLandingState();
    ~CPlayerLandingState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

