#pragma once
#include "CComponent.h"

class CObj;
class CRigidBody :
    public CComponent
{
private:
    Vec2    m_vForce;           // 힘
    Vec2    m_vVelocity;        // 속도
    float   m_fMass;            // 질량

    float   m_fFriction;        // 마찰력
    float   m_fFrictionScale;   // 마찰계수

    // 속도 제한
    float   m_fVelocityLimit;   // 제한속도
    float   m_fGravityVLimit;   // 종단속도

    float   m_fGravityAccel;
    bool    m_bGravityUse;

    bool    m_bGround;          // 지상에 존재하는지
 
public:
    void AddForce(Vec2 _vForce) { m_vForce += _vForce; }
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }

    void SetGravityVelocityLimit(float _fLimit) { m_fGravityVLimit = _fLimit; }

    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }
    Vec2 GetVelocity() { return m_vVelocity; }

    void AddVelocity(Vec2 _vAdd) { m_vVelocity += _vAdd; }

    void SetFriction(float _fFriction) { m_fFriction = _fFriction; }
    float GetFriction() { return m_fFriction; }

    void SetFrictionScale(float _fFrictionScale) { m_fFrictionScale = _fFrictionScale; }
    float GetFrictionScale() { return m_fFrictionScale; }

    void SetGravityAccel(float _fAccel) { m_fGravityAccel = _fAccel; }
    void SetGravity(bool _bSet) { m_bGravityUse = _bSet; }

    void OnGround() { m_bGround = true; m_vVelocity.y = 0; };
    void OffGround() { m_bGround = false; }
    bool IsGround() { return m_bGround; }

public:
    CLONE(CRigidBody);

public:
    CRigidBody(CObj* _pOwner);
    CRigidBody(const CRigidBody& _Other);
    virtual ~CRigidBody();

public:
    virtual void Tick() override;
    virtual void Final_Tick() override;
    virtual void Render(HDC _hDC)   override;
};

