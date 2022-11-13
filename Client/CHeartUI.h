#pragma once
#include "CUI.h"

class CHeartUI :
    public CUI
{
private:
    int m_iLength;

public:
    CLONE(CHeartUI);

public:
    CHeartUI();
    ~CHeartUI();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
};

