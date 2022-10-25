#pragma once
#include "CObj.h"

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

