#pragma once
#include "CObj.h"
class CEffect :
    public CObj
{
public:
    CLONE(CEffect);

public:
    CEffect();
    ~CEffect();

public:
    virtual void Tick();
};

