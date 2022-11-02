#pragma once
#include "CObj.h"

class CTexture;
class CMonster :
    public CObj
{
private:
    CObj* m_pTarget;
    CTexture* m_pTexture;

    tMonsterInfo m_tInfo;

public:
    void SetTarget(CObj* _pTarget) { m_pTarget = _pTarget; }
    tMonsterInfo& GetMonsterInfo() { return m_tInfo; }

public:
    CLONE(CMonster);

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
};

