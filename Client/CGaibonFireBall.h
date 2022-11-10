#pragma once
#include "CMonsterProjectile.h"

class CGaibonFireBall :
    public CMonsterProjectile
{
private:
    float m_fSpeed;

public:
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

public:
    CLONE(CGaibonFireBall);

public:
    CGaibonFireBall();
    ~CGaibonFireBall();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;
};

