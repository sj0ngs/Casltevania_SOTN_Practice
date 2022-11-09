#pragma once
#include "CMonster.h"

enum class EGAIBON_STATE
{
    PHASE_1,
    PHASE_2
};

class CGaibon :
    public CMonster
{
private:
    EGAIBON_STATE  m_eState;

public:
    EGAIBON_STATE GetSlograState() { return m_eState; }
    void ChangeGaibonState(EGAIBON_STATE _eState) { m_eState = _eState; }

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

    virtual void Dead() override;
};

