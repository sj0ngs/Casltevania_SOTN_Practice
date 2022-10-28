#pragma once
#include "CPlayerState.h"
class CPlayerRightMoveState :
    public CPlayerState
{
private:
    float m_fAccWalkTime;

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

