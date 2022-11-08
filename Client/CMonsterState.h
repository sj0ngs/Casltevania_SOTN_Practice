#pragma once
#include "CState.h"

#include "CTimeMgr.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

#define GET_MON() CMonster* pMon = dynamic_cast<CMonster*>(GetOwnerObj());\
                  assert(pMon);

#define GET_PLAYER() CPlayer* pPlayer = dynamic_cast<CPlayer*>(CLevelMgr::GetInst()->GetCurLevel()->GetLayer(ELAYER::PLAYER)[0]);\
                        assert(pPlayer);

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

