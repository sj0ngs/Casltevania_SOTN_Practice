#pragma once
#include "CObj.h"

class CTexture;

class CLetter :
    public CObj
{
private:
    CTexture* m_pTex;

    float m_faccTime;
    float m_fLifeTime;

    BLENDFUNCTION  m_tBlend;

public:
    void SetLetterTex(CTexture* _pTex) { m_pTex = _pTex; }
    void SetLifeTime(float _fLifeTime) { m_fLifeTime = _fLifeTime; }

public:
    CLONE(CLetter);

public:
    CLetter();
    ~CLetter();

public:
    virtual void Tick();
    virtual void Render(HDC _DC);
};

