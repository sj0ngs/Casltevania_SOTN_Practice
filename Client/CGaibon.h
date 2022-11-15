#pragma once
#include "CMonster.h"

class CSlogra;

enum class EGAIBON_STATE
{
    PHASE_1,
    PHASE_2
};

class CGaibon :
    public CMonster
{
private:
    EGAIBON_STATE   m_eState;
    CSlogra*        m_pSlogra;

    bool m_bFly;

    bool m_bDeadSequence;
    float m_faccDeathTime;
    float m_faccDeathEffectSpawnTime;

    bool m_bFallSequence;

public:
    EGAIBON_STATE GetGaibonState() { return m_eState; }
    void ChangeGaibonState(EGAIBON_STATE _eState) { m_eState = _eState; }

    bool IsFly() const { return m_bFly; }
    void SetFly(bool _bFly) { m_bFly = _bFly; }

    CSlogra* GetSlogra();

public:
    CLONE(CGaibon);

public:
    CGaibon();
    ~CGaibon();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;

public:
    virtual void Walk() override;
    virtual void Turn() override;
    void SkyAttack();
    void LandAttack();
    void Landing();

    void SkyFire();
    void LandFire();

    void Wake();
    void Change();
    void PickUp();

    virtual void Dead() override;

private:
    void DeathEffect();
    void DeathStart();
};

