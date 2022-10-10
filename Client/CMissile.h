#pragma once
#include "CObj.h"


class CMissile :
    public CObj
{
private:
    float m_fSpeed;
    float m_fDegree;
    float m_fTime;

public:
    CMissile();
    ~CMissile();

public:
    void SetSpeed(float _fSpeed)
    {
        m_fSpeed = _fSpeed;
    }

    void SetDir(float _fDegree)
    {
        m_fDegree = _fDegree;
    }

public:
    CLONE(CMissile);

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

public:
    virtual void BeginOverlap(CCollider* _pOther) override;
};

