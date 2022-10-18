#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
public:
    CIdleState();
    ~CIdleState();

public:
    CLONE(CState);

public:
    virtual void Tick() override {};
    virtual void Final_Tick() override;
    virtual void Render(HDC _DC) override {};
    virtual void Enter() override;
    virtual void Exit() override;
};

