#pragma once
#include "CLevel.h"

class CStage02 :
    public CLevel
{
public:
    CStage02();
    ~CStage02();

public:
    CLONE_DEACTIVATE(CStage02);

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Enter()    override;
    virtual void Exit() override;
};

