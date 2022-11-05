#pragma once
#include "CMonster.h"

class CBloodSkeleton :
    public CMonster
{
private:
    bool m_bCollapse;
    float m_faccCollapseTime;
    float m_faccReviveTime;

public:
    CLONE(CBloodSkeleton);

public:
    CBloodSkeleton();
    ~CBloodSkeleton();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void Walk() override;
    virtual void Turn() override;

    virtual void Dead() override;

private:
    void Revive();
};

