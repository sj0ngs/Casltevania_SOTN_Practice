#pragma once
#include "CObj.h"

class CPlayer;

class CDaggerCrash :
    public CObj
{
private:
    float m_faccTime;
    bool m_bGateOpen;
    int m_iSpawnCount;
    CObj* m_arrGate[4];

    CPlayer* m_pOwner;
    int m_iDmg;

public:
    void SetOwner(CPlayer* _pOwner) { m_pOwner = _pOwner; }

    void SetDmg(int _iDmg) { m_iDmg = _iDmg; }

public:
    CLONE(CDaggerCrash);

public:
    CDaggerCrash();
    ~CDaggerCrash();

public:
    virtual void Tick() override;

private:
    void CreateGate();
    void ShootDagger();
};

