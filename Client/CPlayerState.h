#pragma once
#include "CState.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

#define GET_PLAYER() CPlayer* pPlayer = (CPlayer*)GetOwnerObj();\

#define SET_ANIM(wstring) SetAnim(pPlayer->GetAnimator()->FindAnimation(wstring));\
                            pPlayer->GetAnimator()->Play(wstring, false);

class CPlayerState :
    public CState
{
private:
    CAnimation* m_pAnim;

public:
    virtual void Final_Tick() override;
    virtual void Exit() override;

public:
    void SetAnim(CAnimation* _pAnim) { m_pAnim = _pAnim; }
    CAnimation* GetAnim() const { return m_pAnim; }

public:
    CLONE_DEACTIVATE(CState);

public:
    CPlayerState();
    ~CPlayerState();

protected:
    void Move();
    void Attack(const wchar_t* strState);
};

