#pragma once
#include "CObj.h"

class CForce :
    public CObj
{
private:
    float m_fAccTime;   // 누적 시간   
    float m_fLifeTime;  // 유지 시간
    float m_fForce;     // 힘 크기
    float m_fRadius;    // 힘 반경

public:
    void SetLifeTime(float _fLifeTime) { m_fLifeTime = _fLifeTime; }
    void SetForceScale(float _fForce) { m_fForce = _fForce; }
    void SetForceRadius(float _fRadius) { m_fRadius = _fRadius; }
    
public:
    CLONE(CForce);

public:
    CForce();
    ~CForce();

public:
    void Tick();
    void Render(HDC _DC);
};

