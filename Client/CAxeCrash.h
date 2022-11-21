#pragma once
#include "CObj.h"

class CPlayer;
class CSprialAxe;

class CAxeCrash :
    public CObj
{
private:
    float m_faccTime;
    bool m_bRotEnd;
    vector<CSprialAxe*> m_vecAxe;

    CPlayer* m_pOwner;
    int m_iDmg;

    bool m_bIsReleased;

public:
    void SetOwner(CPlayer* _pOwner) { m_pOwner = _pOwner; }
    void SetDmg(int _iDmg) { m_iDmg = _iDmg; }

    void Init();

public:
    CLONE(CAxeCrash);

public:
    CAxeCrash();
    ~CAxeCrash();

public:
    virtual void Tick() override;

private:
    void ReleaseAxe();
};

