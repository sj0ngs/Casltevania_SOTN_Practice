#pragma once
#include "CObj.h"

// �÷��̾� �̵� ���� ����
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

    EPLAYER_ANIM_STATE m_eState;     // �ִϸ��̼� ����
    EPLAYER_ANIM_STATE m_ePrevState;     // ���� �ִϸ��̼� ����

    int m_iFaceDir;     // �ٶ󺸴� ����(-1 : ����, 1 : ������)
    int m_iPrevFaceDir;     // ���� ������ �ٶ󺸴� ����

    float m_fRunStartAcc;   // ���� �޸��� ���� �ð�
    float m_fJumpTimeAcc;   // ���� ü���ð�

    bool m_bDoubleJump;     // ���� ���� ���� ����
    
    unsigned int m_iMoveState;      // �̵� ����

public:
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
    void SetDir(Vec2 _vDir) { m_vDir = _vDir; }
    Vec2 GetDir() const { return m_vDir; }
    EPLAYER_ANIM_STATE GetPlayerState()  const { return m_eState; }
    int GetMoveState() const { return m_iMoveState; }
    void SetMoveState(int _iMoveState) { m_iMoveState = _iMoveState; }

    // �÷����� �����ϸ� ���� ���� ��ġ���� �������ִ� �Լ�
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

