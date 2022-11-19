#pragma once
#include "CLevel.h"

class CRewardLevel :
    public CLevel
{
public:
    CLONE_DEACTIVATE(CRewardLevel);

public:
    CRewardLevel();
    ~CRewardLevel();

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
    virtual void Enter()    override;
    virtual void Exit() override;
};

