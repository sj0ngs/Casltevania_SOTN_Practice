#pragma once
#include "CEntity.h"
#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;
class CAI;

class CObj :
    public CEntity
{
private: // �� ������ ã�� �����ϱ� ���� ��������� �Լ��� ���� ���� �����Ѵ�
    Vec2        m_vPos;  // ��ġ ����
    Vec2        m_vScale; // ���� ���� ���� ����

    Vec2        m_vDir;     // ���󿡼��� �̵�����(�缱 �̵��� �ʿ���)
    Vec2        m_PrevPos;

    // Component
    CCollider*  m_pCollider;
    CAnimator*  m_pAnimator;
    CRigidBody* m_pRigidBody;
    CAI*        m_pAI;

    bool m_bDead;

public: 
    void SetPos(Vec2 _pt) { m_vPos = _pt; }
    Vec2 GetPos() { return m_vPos; }

    void SetScale(Vec2 _pt) { m_vScale = _pt; }
    Vec2 GetScale() { return m_vScale; }

    void SetDir(Vec2 _vDir) { m_vDir = _vDir; }
    Vec2 GetDir() const { return m_vDir; }

    Vec2 GetPrevPos() { return m_PrevPos; }

    void CreateCollider();
    CCollider* GetCollider() { return m_pCollider; }

    void CreateAnimator();
    CAnimator* GetAnimator() { return m_pAnimator; }

    void CreateRigidBody();
    CRigidBody* GetRigidBody() { return m_pRigidBody; }

    void CreateAI();
    CAI* GetAI() { return m_pAI; }
    
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

public:
    virtual void Save(FILE* _pFile) {};
    virtual void Load(FILE* _pFile) {};
};

