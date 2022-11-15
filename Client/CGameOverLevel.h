#pragma once
#include "CLevel.h"

class CGameOverLevel :
    public CLevel
{
public:
    CLONE_DEACTIVATE(CGameOverLevel);

public:
    CGameOverLevel();
    ~CGameOverLevel();

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Enter()    override;
    virtual void Exit() override;
};

