#pragma once
#include "CLevel.h"

class CEditorLevel :
    public CLevel
{
public:
    CEditorLevel();
    ~CEditorLevel();

public:
    CLONE_DEACTIVATE(CEditorLevel);

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Enter()    override;
    virtual void Exit() override;
};

