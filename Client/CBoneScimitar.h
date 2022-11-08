#pragma once
#include "CMonster.h"

class CBoneScimitar :
    public CMonster
{
private:
    bool m_bAttackEnd;

public:
    CLONE(CBoneScimitar);

public:
    CBoneScimitar();
    ~CBoneScimitar();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void Idle() override;
    virtual void Walk() override;
    virtual void Turn() override;
    virtual void Attack() override;

    virtual void Dead() override;

private:
    void Slash();
};

