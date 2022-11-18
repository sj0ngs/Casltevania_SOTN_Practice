#pragma once
#include "CPlayerProjectile.h"

class CPlayer;
class CEffect;

class CBibleCrash :
    public CPlayerProjectile
{
private:
    CPlayer* m_pOwner;
    CEffect* m_pEffect;

    bool m_bOnCollider;

    float m_faccTime;

    bool m_bHit;

public:
    void SetOwner(CPlayer* _pOwner);

public:
    CLONE(CBibleCrash);

public:
    CBibleCrash();
    ~CBibleCrash();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;
};

