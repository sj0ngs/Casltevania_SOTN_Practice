#pragma once
#include "CEntity.h"
#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;

class CObj :
    public CEntity
{
private: // �� ������ ã�� �����ϱ� ���� ��������� �Լ��� ���� ���� �����Ѵ�
    Vec2        m_vPos;  // ��ġ ����
    Vec2        m_vScale; // ���� ���� ���� ����

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

