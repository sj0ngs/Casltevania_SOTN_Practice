#pragma once
#include "CPlayerState.h"
class CPlayerRightMoveState :
    public CPlayerState
{
public:
    CLONE(CPlayerRightMoveState);

public:
    CPlayerRightMoveState();
    ~CPlayerRightMoveState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

