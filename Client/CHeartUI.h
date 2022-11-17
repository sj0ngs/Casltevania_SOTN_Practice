#pragma once
#include "CUI.h"

class CHeartUI :
    public CUI
{
private:
    BLENDFUNCTION  m_tBlend;
    float m_fRatio;

    float m_fDir;

public:
    CLONE(CHeartUI);

public:
    CHeartUI();
    ~CHeartUI();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
};

