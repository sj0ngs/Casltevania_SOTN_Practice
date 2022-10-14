#pragma once
#include "CCollider.h"

class CObj;

class CLineCollider :
    public CCollider
{
private:
    Vec2 m_vPos1;
    Vec2 m_vPos2;

public:
    CLONE(CLineCollider);

public:
    CLineCollider(CObj* _pOwner);
    ~CLineCollider();

public:
    virtual void Render(HDC _DC)   override;
};

