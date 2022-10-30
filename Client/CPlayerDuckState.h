#pragma once
#include "CPlayerState.h"
class CPlayerDuckState :
    public CPlayerState
{
public:
    CLONE(CPlayerDuckState);

public:
    CPlayerDuckState();
    ~CPlayerDuckState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;

};

