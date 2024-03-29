#pragma once
#include "CPlayerState.h"

class CPlayerMoveLeftState :
    public CPlayerState
{
public:
    CLONE(CPlayerMoveLeftState);

public:
    CPlayerMoveLeftState();
    ~CPlayerMoveLeftState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

