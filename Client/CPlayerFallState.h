#pragma once
#include "CPlayerState.h"

class CPlayerFallState :
    public CPlayerState
{
public:
    CLONE(CPlayerFallState);

public:
    CPlayerFallState();
    ~CPlayerFallState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

