#pragma once
#include "CObj.h"

class CTexture;
class CMonster :
    public CObj
{
private:
    tMonsterInfo m_tInfo;
    bool m_bOnAttack;

protected:
    float m_faccAttackTime;

public:
    tMonsterInfo& GetMonsterInfo() { return m_tInfo; }
    void SetMonsterInfo(tMonsterInfo& _tInfo) { m_tInfo = _tInfo; }

    bool IsAttack() const { return m_bOnAttack; }
    void SetOnAttack(bool _bOnAttack) { m_bOnAttack = _bOnAttack; }

public:
    CLONE_DEACTIVATE(CMonster);

public:
    CMonster();
    ~CMonster();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;

public:
    void TakeDamage(int _iDmg);
    virtual void Idle() {};
    virtual void Walk() = 0;
    virtual void Turn();
    virtual void Attack() {};

    virtual void Dead() = 0;
};

