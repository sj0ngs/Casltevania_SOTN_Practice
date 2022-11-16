#pragma once
#include "CPlayerProjectile.h"

class CTexture;

class CHellFire :
    public CPlayerProjectile
{
private:
    float m_fSpeed;
    CTexture* m_pTex;
    float m_faccTime;

    float m_fTheta;

    float m_fRatio;
    float m_fDir;

    bool m_bIsFire;

public:
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

public:
    CLONE(CHellFire);

public:
    CHellFire();
    ~CHellFire();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;

public:
    virtual void Dead() override;

private:
    void Effect();
};

