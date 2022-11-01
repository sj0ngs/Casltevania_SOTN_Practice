#pragma once
#include "CPlayerAttackState.h"
class CPlayerJumpAttackState :
    public CPlayerAttackState
{
public:
    CLONE(CPlayerJumpAttackState);

public:
    CPlayerJumpAttackState();
    ~CPlayerJumpAttackState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
};

