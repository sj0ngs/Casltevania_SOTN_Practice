#pragma once
#include "CObj.h"

// 플레이어 이동 제한 상태
#define FALL_BLOCK 0x1
#define LEFT_BLOCK 0x2
#define RIGHT_BLOCK 0x4
#define UP_BLOCK 0x8
#define DOWN_BLOCK 0x10
#define DUCK 0x20

enum class EPLAYER_ANIM_STATE : UINT8
{
    IDLE1,
    WALK_START_LEFT,
    WALK_START_RIGHT,
    WALK_LEFT,
    WALK_RIGHT,
    TURN_AROUND_LEFT,
    TURN_AROUND_RIGHT,
    JUMP,
    DOULBE_JUMP,
    SUPER_JUMP,
    FALL,
    DUCK_DOWN,
    DUCK_UP,
    ATTACK,
    END
};

class CTexture;
class CPlayer :
    public CObj
{
private:
    float m_fSpeed;
    Vec2 m_vDir;

    EPLAYER_ANIM_STATE m_eState;     // 애니메이션 상태
    EPLAYER_ANIM_STATE m_ePrevState;     // 이전 애니메이션 상태

    int m_iFaceDir;     // 바라보는 방향(-1 : 왼쪽, 1 : 오른쪽)
    int m_iPrevFaceDir;     // 이전 프레임 바라보던 방향

    float m_fRunStartAcc;   // 누적 달리기 시작 시간
    float m_fJumpTimeAcc;   // 누적 체공시간

    bool m_bDoubleJump;     // 더블 점프 가능 여부
    
    unsigned int m_iMoveState;      // 이동 상태

public:
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
    void SetDir(Vec2 _vDir) { m_vDir = _vDir; }
    Vec2 GetDir() const { return m_vDir; }
    EPLAYER_ANIM_STATE GetPlayerState()  const { return m_eState; }
    int GetMoveState() const { return m_iMoveState; }
    void SetMoveState(int _iMoveState) { m_iMoveState = _iMoveState; }

    // 플랫폼에 착지하면 점프 관련 수치들을 리셋해주는 함수
    void ResetJump() { m_bDoubleJump = true; m_fJumpTimeAcc = 0.f; }

public:
    CLONE(CPlayer);

public:
    CPlayer();
    ~CPlayer();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)    override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

public:
    void ChangeAnim();
};

