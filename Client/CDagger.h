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

public:
    CDagger();
    ~CDagger();

public:
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

public:
    CLONE(CDagger);

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;
};

