#pragma once
#include "CPlayerState.h"
#include "CAttack.h"

class CPlayerAttackState :
    public CPlayerState
{
private:
    CAttack* m_pAttack;

public:
    void SetAttack(CAttack* _pAttack) { m_pAttack = _pAttack; }
    CAttack* GetAttack() const { return m_pAttack; }

public:
    CLONE_DEACTIVATE(CPlayerAttackState);

public:
    CPlayerAttackState();
    ~CPlayerAttackState();

public:
    virtual void Enter() override;
    virtual void Exit() override;
};

