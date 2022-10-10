#pragma once
#include "CEntity.h"
#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;

class CObj :
    public CEntity
{
private: // 논리 오류를 찾기 쉽게하기 위해 멤버변수를 함수를 통해 따로 접근한다
    Vec2        m_vPos;  // 위치 정보
    Vec2        m_vScale; // 가로 세로 길이 정보

    // Component
    CCollider*  m_pCollider;
    CAnimator*  m_pAnimator;
    CRigidBody* m_pRigidBody;

    bool m_bDead;

public: 
    void SetPos(Vec2 _pt) { m_vPos = _pt; }
    Vec2 GetPos() { return m_vPos; }

    void SetScale(Vec2 _pt) { m_vScale = _pt; }
    Vec2 GetScale() { return m_vScale; }

    void CreateCollider();
    CCollider* GetCollider() { return m_pCollider; }

    void CreateAnimator();
    CAnimator* GetAnimator() { return m_pAnimator; }

    void CreateRigidBody();
    CRigidBody* GetRigidBody() { return m_pRigidBody; }
    
public:
    bool IsDead() { return m_bDead; }
    void SetDead();
    
public:
    CObj();
    CObj(const CObj& _Other);
    virtual ~CObj();

    friend class CEventMgr;

public:
    virtual CObj* Clone() = 0;

public:
    virtual void Tick();
    virtual void Final_Tick()   final;
    virtual void Render(HDC _DC);

    virtual void BeginOverlap(CCollider* _pOther);
    virtual void OnOverlap(CCollider* _pOther);
    virtual void EndOverlap(CCollider* _pOther);
};

