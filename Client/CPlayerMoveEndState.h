#pragma once
#include "CPlayerState.h"
class CPlayerMoveEndState :
    public CPlayerState
{
public:
    CLONE(CPlayerMoveEndState);

public:
    CPlayerMoveEndState();
    ~CPlayerMoveEndState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

