#pragma once
#include "CPlayerProjectile.h"

class CBible :
    public CPlayerProjectile
{
private:
    float m_fSpeed;
    float m_fRadius;
    float m_fAngle;
    float m_fDegree;

    float m_fAccTime;
    float m_fSpawnTime;
    CObj* m_pCenter;

    CTexture* m_pTex;

public:
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
    void SetCenter(CObj* _pCenter) { m_pCenter = _pCenter; }
public:
    CLONE(CBible);

public:
    CBible();
    ~CBible();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;
};

