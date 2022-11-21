#pragma once
#include "CPlayerProjectile.h"

class CSprialAxe :
    public CPlayerProjectile
{
private:
    float m_fSpeed;
    float m_fRadius;
    float m_fAngle;
    float m_fDegree;

    float m_fAccTime;

    bool m_bOnThrow;
    
    Vec2 m_vCenter;

public:
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
    void SetCenter(Vec2 _vCenter) { m_vCenter = _vCenter; }
    void SetAngle(float _fAngle) { m_fAngle = _fAngle; }

    void SetOnThrow(bool _bOnThrow) { m_bOnThrow = _bOnThrow; }

public:
    CLONE(CSprialAxe);

public:
    CSprialAxe();
    ~CSprialAxe();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;
};

