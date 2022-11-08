#pragma once
#include "CMonster.h"

enum class EAXE_ARMOR_ATTACK
{
    THROW_HIGH,
    THROW_MIDDLE,
    THROW_LOW,
    SLASH,

    NONE
};

class CAxeArmor :
    public CMonster
{
private:
    bool m_bAttackEnd;
    EAXE_ARMOR_ATTACK m_eState;

public:
    CLONE(CAxeArmor);

public:
    CAxeArmor();
    ~CAxeArmor();

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
    void Throw();
};

