#pragma once
#include "CObj.h"

class CTexture;

class CSubWeapon :
    public CObj
{
private:
    ESUB_WEAPON_TYPE m_eType;
    CTexture* m_pTex;

    Vec2 vOffsetPos;

public:
    void SetSubWeaponType(ESUB_WEAPON_TYPE _eType);

public:
    CLONE(CSubWeapon);

public:
    CSubWeapon();
    ~CSubWeapon();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;
};

