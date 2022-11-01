#pragma once
#include "CPlayerState.h"
class CPlayerGetUp :
    public CPlayerState
{
public:
    CLONE(CPlayerGetUp);

public:
    CPlayerGetUp();
    ~CPlayerGetUp();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

