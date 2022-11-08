#pragma once
#include "CMonsterProjectile.h"

class CMonsterAxe :
    public CMonsterProjectile
{
private:
    float m_fSpeed;
    float m_faccTurnTime;

    bool m_bIsTurn;

public:
    CLONE(CMonsterAxe);

public:
    CMonsterAxe();
    ~CMonsterAxe();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;

private:
    void Turn();
};

