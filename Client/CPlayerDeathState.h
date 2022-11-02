#pragma once
#include "CPlayerState.h"
class CPlayerDeathState :
    public CPlayerState
{
public:
    CLONE(CPlayerDeathState);

public:
    CPlayerDeathState();
    ~CPlayerDeathState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

