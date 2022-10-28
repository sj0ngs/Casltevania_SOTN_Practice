#pragma once
#include "CState.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

class CPlayerState :
    public CState
{
public:
    CPlayerState();
    ~CPlayerState();
};

