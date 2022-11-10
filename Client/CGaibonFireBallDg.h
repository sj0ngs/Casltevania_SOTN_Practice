#pragma once
#include "CMonsterProjectile.h"

class CGaibonFireBallDg :
    public CMonsterProjectile
{
private:
    float m_fSpeed;

public:
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

public:
    CLONE(CGaibonFireBallDg);

public:
    CGaibonFireBallDg();
    ~CGaibonFireBallDg();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;
};

