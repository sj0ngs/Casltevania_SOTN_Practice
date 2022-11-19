#pragma once
#include "CObj.h"

#define SMALL_HEART_MOVE 1.f

enum class EHEART_TYPE
{
    SMALL_HEART,
    LARGE_HEART,
    HP_HEART,

    NONE
};

class CHeart :
    public CObj
{
private:
    EHEART_TYPE m_eType;

    int         m_iHealValue;

    float       m_faccMoveTime;
    int         m_iDir;
    float       m_fDegree;

    float       m_faccDeathTime;

    bool        m_bDeadSoon;

public:
    void SetHeartType(EHEART_TYPE _eType);

public:
    CLONE(CHeart);

public:
    CHeart();
    ~CHeart();

public:
    virtual void Tick();

public:
    virtual void BeginOverlap(CCollider* _pOther) override;

private:
    void SmallHeartMove();
};

