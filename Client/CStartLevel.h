#pragma once
#include "CLevel.h"

class CStartLevel :
    public CLevel
{
public:
    CStartLevel();
    ~CStartLevel();

public:
    CLONE_DEACTIVATE(CStartLevel);

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Enter()    override;
    virtual void Exit() override;
};

