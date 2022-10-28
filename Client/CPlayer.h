#pragma once
#include "CObj.h"

enum class EPLAYR_ANIM : UINT8
{
    IDLE_RIGHT,
    IDLE_LEFT,

    WALK_START_RIGHT,
    WALK_START_LEFT,
    WALK_RIGHT,
    WALK_LEFT,

    JUMP_RIGHT,
    JUMP_LEFT,

    FALL_RIGHT,
    FALL_LEFT,

    END
};

//wstring g_arrPlayerAnim[(UINT)EPLAYR_ANIM::END] =
//{
//    L"Idle_Right",
//    L"Idle_Left",
//
//    L"Walk_Start_Right",
//    L"Walk_Start_Left",
//    L"Walk_Right",
//    L"Fall_Right",
//    L"Fall_Left"
//
//    L"Jump_Right",
//    L"Jump_Left",
//    L"Jump_Right",
//};


class CTexture;
class CPlayer :
    public CObj
{
private:
    float m_fSpeed;

    bool m_bPrevFaceDir;     // ���� ������ �ٶ󺸴� ����

    float m_fRunStartAcc;   // ���� �޸��� ���� �ð�
    float m_fJumpTimeAcc;   // ���� ü���ð�

    bool m_bDoubleJump;     // ���� ���� ���� ����

public:
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
    float GetSpeed() const { return m_fSpeed; }

    bool IsFaceDirChange() { return m_bPrevFaceDir != GetFaceDir(); };

    // �÷����� �����ϸ� ���� ���� ��ġ���� �������ִ� �Լ�
    void ResetJump() { m_bDoubleJump = true; m_fJumpTimeAcc = 0.f; }

    void EndJump() { m_fJumpTimeAcc = 6.f; }

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
};

