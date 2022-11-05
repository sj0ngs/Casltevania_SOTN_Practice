#pragma once
#include "CState.h"

#include "CTimeMgr.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

#define GET_MON() CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());\
                  assert(pMon);

class CMonsterState :
    public CState
{
public:
    CLONE_DEACTIVATE(CState);

public:
    CMonsterState();
    ~CMonsterState();

public:
    virtual void Final_Tick() override;
    virtual void Exit() override;

public:
    void Dead();
};

