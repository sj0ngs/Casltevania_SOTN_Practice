#pragma once
#include "CPlayerState.h"

class CPlayerAttackState :
    public CPlayerState
{
public:
    CLONE(CPlayerAttackState);

public:
    CPlayerAttackState();
    ~CPlayerAttackState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

