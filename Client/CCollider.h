#pragma once
#include "CComponent.h"

class CObj;

class CCollider :
    public CComponent
{
private:
    Vec2 m_vOffsetPos;
    Vec2 m_vFinalPos;

    Vec2 m_vScale;

    int m_iOverlapCount;

public:
    void SetOffsetPos(Vec2 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }

    Vec2 GetOffsetPos() { return m_vOffsetPos; }

    void SetFinalPos(Vec2 _vFinalPos) { m_vFinalPos = _vFinalPos; }

    Vec2 GetFinalPos() { return m_vFinalPos; }

    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

    Vec2 GetScale() { return m_vScale; }

public:
    CLONE(CCollider);

public:
    CCollider(CObj* _pOwner);
    CCollider(const CCollider& _Other);
    ~CCollider();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    void BeginOverlap(CCollider* _pOther);
    void OnOverlap(CCollider* _pOther);
    void EndOverlap(CCollider* _pOther);
};

