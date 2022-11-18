#pragma once
#include "CObj.h"

class CParticle :
    public CObj
{
private:
    CObj* m_pTarget;

public:
    void SetTarget(CObj* _pTarget) { m_pTarget = _pTarget; }

public:
    CLONE(CParticle);

public:
    CParticle();
    ~CParticle();

public:
    virtual void Tick();

public:
    void SetFrm(UINT _iFrm);
};

