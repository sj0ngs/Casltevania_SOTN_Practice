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
private: // 논리 오류를 찾기 쉽게하기 위해 멤버변수를 함수를 통해 따로 접근한다
    Vec2        m_vPos;     // 위치 정보
    Vec2        m_vScale;   // 가로 세로 길이 정보
    ELAYER      m_eLayer;   // 자신이 속해있는 레이어

    Vec2        m_vDir;     // 지상에서의 이동방향(사선 이동에 필요함)
    Vec2        m_PrevPos;

    bool         m_bFaceDir;     // 바라보는 방향 오른쪽 ture / 왼쪽 false

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

    void SetLayer(ELAYER _eLayer) { m_eLayer = _eLayer; }
    ELAYER GetLayer() const { return m_eLayer; }

    void SetDir(Vec2 _vDir) { m_vDir = _vDir; }
    Vec2 GetDir() const { return m_vDir; }

    Vec2 GetPrevPos() { return m_PrevPos; }

    void SetFaceDir(bool _bFaceDir) { m_bFaceDir = _bFaceDir; }
    bool GetFaceDir() const { return m_bFaceDir; }

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

