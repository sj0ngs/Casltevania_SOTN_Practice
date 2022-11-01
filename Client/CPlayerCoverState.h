#pragma once
#include "CPlayerState.h"
#include "CCover.h"

class CPlayerCoverState :
    public CPlayerState
{
private:
    CCover* m_pCover;

public:
    void SetCover(CCover* _pCover) { m_pCover = _pCover; }
    CCover* GetCover() const { return m_pCover; }

public:
    CLONE_DEACTIVATE(CPlayerCoverState);

public:
    CPlayerCoverState();
    ~CPlayerCoverState();

public:
    virtual void Enter() override;
    virtual void Exit() override;
};
