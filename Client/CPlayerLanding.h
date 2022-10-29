#pragma once
#include "CPlayerState.h"
class CPlayerLanding :
    public CPlayerState
{
public:
    CLONE(CPlayerLanding);

public:
    CPlayerLanding();
    ~CPlayerLanding();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

