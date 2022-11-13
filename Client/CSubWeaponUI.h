#pragma once
#include "CUI.h"

class CTexture;

class CSubWeaponUI :
    public CUI
{
private:
    ESUB_WEAPON_TYPE    m_eType;
    CTexture* m_pTex;

public:
    CLONE(CSubWeaponUI);

public:
    CSubWeaponUI();
    ~CSubWeaponUI();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
};

