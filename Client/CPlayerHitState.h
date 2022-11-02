#pragma once
#include "CPlayerState.h"

class CPlayerHitState :
    public CPlayerState
{
public:
    CLONE(CPlayerHitState);

public:
    CPlayerHitState();
    ~CPlayerHitState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

