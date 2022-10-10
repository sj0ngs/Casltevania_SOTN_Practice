#pragma once
#include "CObj.h"

class CForce :
    public CObj
{
private:
    float m_fAccTime;   // ���� �ð�   
    float m_fLifeTime;  // ���� �ð�
    float m_fForce;     // �� ũ��
    float m_fRadius;    // �� �ݰ�

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

