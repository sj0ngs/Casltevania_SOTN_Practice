#pragma once
#include "CObj.h"

class CBench :
    public CObj
{
private:
    static bool m_bBroken;

public:
    CLONE(CBench);

public:
    CBench();
    CBench(const CBench& _pOther);
    ~CBench();

public:
    virtual void BeginOverlap(CCollider* _pOther) override;
};

