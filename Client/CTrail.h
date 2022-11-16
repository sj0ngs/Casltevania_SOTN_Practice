#pragma once
#include "CObj.h"

class CTexture;

class CTrail :
    public CObj
{
private:
    CTexture* m_pTex;
    tAnimFrm m_tAnimFrm;

    float m_faccLifeTime;
    float m_fLifeTime;

    BLENDFUNCTION  m_tBlend;

    float m_fRatio;

public:
    void SetTrailTex(CTexture* _pTex) { m_pTex = _pTex; }

    void SetAnimFrm(const tAnimFrm& _tFrm) { m_tAnimFrm = _tFrm; }

    void SetLifeTime(float _fLifeTime) { m_fLifeTime = _fLifeTime; }

public:
    CLONE(CTrail);

public:
    CTrail();
    ~CTrail();

public:
    virtual void Tick()  override;
    virtual void Render(HDC _DC) override;
};

