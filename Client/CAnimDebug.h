#pragma once

#include "CObj.h"
class CAnimDebug :
    public CObj
{
private:

public:
    CLONE_DEACTIVATE(CAnimDebug);

public:
    CAnimDebug();
    ~CAnimDebug();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
};

