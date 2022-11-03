#pragma once
#include "CObj.h"

#include "CTimeMgr.h"
#include "CCollider.h"

class CProjectile :
    public CObj
{
private:
    int m_iDmg;

public:
    void SetDamage(int _iDmg) { m_iDmg = _iDmg; }
    int GetDamage() const { return m_iDmg; }

public:
    CLONE_DEACTIVATE(CProjectile);

public:
    CProjectile();
    ~CProjectile();

public:
    virtual void Render(HDC _DC) override;

    virtual void BeginOverlap(CCollider* _pOther) override {};
    virtual void OnOverlap(CCollider* _pOther) override {};
    virtual void EndOverlap(CCollider* _pOther) override {};

public:
    void MapOut();
    virtual void Dead();
};

