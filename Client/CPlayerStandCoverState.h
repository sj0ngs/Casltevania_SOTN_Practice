#pragma once
#include "CPlayerCoverState.h"

class CPlayerStandCoverState :
    public CPlayerCoverState
{
public:
    CLONE(CPlayerStandCoverState);

public:
    CPlayerStandCoverState();
    ~CPlayerStandCoverState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
};

