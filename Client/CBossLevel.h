#pragma once
#include "CLevel.h"

class CBossLevel :
    public CLevel
{
public:
    CLONE_DEACTIVATE(CBossLevel);

public:
    CBossLevel();
    ~CBossLevel();

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Enter()    override;
    virtual void Exit() override;
};

