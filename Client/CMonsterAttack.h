#pragma once
#include "CMonsterProjectile.h"

class CMonster;

class CMonsterAttack :
    public CMonsterProjectile
{
private:
    float m_faccLifeTime;
    float m_fLifeSpan;
    CMonster* m_pOwner;
    

public:
    void SetLifeSpan(float _fLifeSpan) { m_fLifeSpan = _fLifeSpan; }

    void SetOwner(CMonster* _pOwner) { m_pOwner = _pOwner; }

public:
    CLONE(CMonsterAttack);

public:
    CMonsterAttack();
    ~CMonsterAttack();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override {};

};

