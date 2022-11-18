#pragma once
#include "CTrigger.h"

class CParticle;

class CSaveTrigger :
    public CTrigger
{
private:
    vector<CParticle*> m_vecParticle;
    bool m_bReleased;

public:
    CLONE(CSaveTrigger);

public:
    CSaveTrigger();
    ~CSaveTrigger();

public:
    virtual void Render(HDC _DC) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

public:
    void AddParticle(CParticle* _pParticle);
    void ReleaseParticle();
};

