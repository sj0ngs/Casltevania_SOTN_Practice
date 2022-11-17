#pragma once
#include "CUI.h"

class CTexture;

class CHP :
    public CUI
{
public:
    CLONE(CHP);

public:
    CHP();
    ~CHP();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
};

