#pragma once
#include "CUI.h"

class CMPBar :
    public CUI
{
private:
    float m_fRatio;

public:
    CLONE(CMPBar);

public:
    CMPBar();
    ~CMPBar();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
};

