#pragma once
#include "CUI.h"

class CHUD :
    public CUI
{
public:
    CLONE(CHUD);

public:
    CHUD();
    ~CHUD();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
};

