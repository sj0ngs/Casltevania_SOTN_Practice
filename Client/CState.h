#pragma once
#include "CEntity.h"

#include "CAI.h"
#include "CObj.h"

class CState :
    public CEntity
{
private:
    AI* m_pOwnerAI;    // 자신을 소유하고 있는 AI Component

public:
    AI* GetOwnerAI() const { return m_pOwnerAI; }
    CObj* GetOwnerObj() const { return m_pOwnerAI->GetOwner(); }


public:
    CLONE_DEACTIVATE(CState);

public:
    CState();
    ~CState();

public:
    virtual void Final_Tick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    void ChangeState(const wchar_t* _pStateName);

    friend class AI;
};

