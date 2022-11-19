#pragma once
#include "CPlayerProjectile.h"

class CTexture;

class CDagger :
	public CPlayerProjectile
{
private:
    float m_fSpeed;
    CTexture* m_pRightTex;
    CTexture* m_pLeftTex;

    float m_faccTime;

public:
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

public:
    CLONE(CDagger);

public:
    CDagger();
    ~CDagger();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;

public:
    virtual void Dead() override;
};

