#pragma once
#include "CMonster.h"

const float SLOGRA_ATTACK_COOL = 3.f;
const float SLOGRA_FIRE_COOL = 10.f;

enum class ESLOGRA_STATE
{
    SPEAR,
    BEAK
};

class CSlogra :
    public CMonster
{
private:
    ESLOGRA_STATE m_eState;

    bool m_bAttackEnd;
    float m_faccAttackCool;
    bool m_bCanAttack;

    bool m_bCanFire;
    bool m_bFireEnd;
    float m_faccFireCool;

    bool m_bDeadSequence;
    float m_faccDeathTime;
    float m_faccDeathEffectSpawnTime;

    bool m_bIsHit;
    bool m_bIsCatch;

public:
    ESLOGRA_STATE GetSlograState() { return m_eState; }
    void ChangeSlograState(ESLOGRA_STATE _eState) { m_eState = _eState; }

    bool SlograCanAttack() const { return m_bCanAttack; }

    bool SlograCanFire() const { return m_bCanFire; }
    void SlograStartFire() { m_bCanFire = false; }

    void SetSlograHit(bool _bIsHit) { m_bIsHit = _bIsHit; }
    bool IsSlograHit() const { return m_bIsHit; }

    void SetSlograCatch(bool _bIsCatch) { m_bIsCatch = _bIsCatch; }
    bool IsSlograCatch() const { return m_bIsCatch; }

public:
    CLONE(CSlogra);

public:
    CSlogra();
    ~CSlogra();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;

public:
    virtual void Idle() override;
    virtual void Walk() override;
    virtual void Turn() override;
    virtual void Attack() override;
    void Hit();
    void Fire();

    void Wake();
    void Drop();

    virtual void Dead() override;

private:
    void Sting();
    void DeathEffect();
};

