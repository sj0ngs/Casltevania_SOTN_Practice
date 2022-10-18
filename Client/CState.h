#pragma once
#include "CEntity.h"

class CAI;

class CState :
    public CEntity
{
private:
    CAI* m_pOwnerAI;    // 자신을 소유하고 있는 AI Component

public:
    CLONE(CState);

public:
    CState();
    ~CState();

public:
    virtual void Final_Tick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;
};

