#pragma once
#include "CPlayerCoverState.h"

class CPlayerDuckCoverState :
    public CPlayerCoverState
{
public:
    CLONE(CPlayerDuckCoverState);

public:
    CPlayerDuckCoverState();
    ~CPlayerDuckCoverState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
};

