#pragma once
#include "CLevel.h"

class CStage03 :
    public CLevel
{
public:
    CStage03();
    ~CStage03();

public:
    CLONE_DEACTIVATE(CStage03);

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Enter()    override;
    virtual void Exit() override;
};

