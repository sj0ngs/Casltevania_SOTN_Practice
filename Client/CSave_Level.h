#pragma once
#include "CLevel.h"

class CTexture;

class CSave_Level :
    public CLevel
{
public:
    CLONE_DEACTIVATE(CSave_Level);

public:
    CSave_Level();
    ~CSave_Level();

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
    virtual void Enter()    override;
    virtual void Exit() override;

private:
    void SetTrigger();
};

