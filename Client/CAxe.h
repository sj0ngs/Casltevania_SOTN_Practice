#pragma once
#include "CPlayerProjectile.h"

class CAxe :
    public CPlayerProjectile
{
private:
    CTexture* m_pRightTex;
    CTexture* m_pLeftTex;

public:
    CLONE(CAxe);

public:
    CAxe();
    ~CAxe();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;
};

