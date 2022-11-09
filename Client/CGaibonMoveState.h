#pragma once
#include "CMonsterState.h"

class CGaibonMoveState :
    public CMonsterState
{
private:
    Vec2 vDest;
        
public:
    CLONE(CGaibonMoveState);

public:
    CGaibonMoveState();
    ~CGaibonMoveState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

