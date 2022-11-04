#pragma once
#include "CObj.h"

class CTexture;

class CBibleTrail :
    public CObj
{
private:
    CTexture* m_pTex;
    float m_fLifeTime;

public:
    CLONE(CBibleTrail);

public:
    CBibleTrail();
    ~CBibleTrail();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;
};

