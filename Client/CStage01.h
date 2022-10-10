#pragma once
#include "CLevel.h"
class CStage01 :
    public CLevel
{
public:
    CStage01();
    ~CStage01();

public:
    CLONE_DEACTIVATE(CStage01);

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Enter()    override;
    virtual void Exit() override;
};

