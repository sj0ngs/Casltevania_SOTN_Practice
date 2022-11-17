#pragma once
#include "CObj.h"

enum class EDMG_TYPE
{
    PLAYER,
    MONSTER,
    
    NONE
};

class CTexture;

class CDamage :
    public CObj
{
private:
    UINT m_iDmg;
    CTexture* m_pTex;

    EDMG_TYPE   m_eType;

    UINT m_iWidth;

    float m_faccTime;

    BLENDFUNCTION  m_tBlend;

public:
    void SetDmg(UINT _iDmg) { m_iDmg = _iDmg; }
    UINT GetDmg() const { return m_iDmg; }

    void SetDmgType(EDMG_TYPE _eType);
    EDMG_TYPE GetDmgType() const { return m_eType; }

public:
    CLONE(CDamage);

public:
    CDamage();
    ~CDamage();

public:
    virtual void Tick();
    virtual void Render(HDC _DC);
};

