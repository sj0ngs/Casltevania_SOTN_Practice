#pragma once
#include "CUI.h"

class CTexture;

class CHP :
    public CUI
{
private:
    int m_iLength;
    Vec2 m_arrPos[4];

public:
    CLONE(CHP);

public:
    CHP();
    ~CHP();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
};

