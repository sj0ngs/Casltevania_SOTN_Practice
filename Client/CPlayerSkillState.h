#pragma once
#include "CPlayerState.h"

class CPlayerSkillState :
    public CPlayerState
{
public:
    bool m_bSkillEnd;

public:
    CLONE(CPlayerSkillState);

public:
    CPlayerSkillState();
    ~CPlayerSkillState();

public:
    virtual void Final_Tick() override;
    virtual void Enter() override;
    virtual void Exit() override;
};

