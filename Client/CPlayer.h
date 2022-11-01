#pragma once
#include "CObj.h"

const float ATTACK_COOL = 0.7f;

class CTexture;
class CWeapon;
class CPlayer :
    public CObj
{
private:
    tPlayerInfo m_tInfo;

    bool m_bPrevFaceDir;     // 이전 프레임 바라보던 방향
    bool m_bDoubleJump;     // 더블 점프 가능 여부
    bool m_bGoDown;         // 아래로 떨어지는지 가능 여부

    bool m_bIsDuck;

    EPLAYER_STATE m_eState;

    float m_fAttackAcc;

    CWeapon* m_pWeapon;

public:
    const tPlayerInfo& GetPlayerInfo() const { return m_tInfo; }

    bool IsFaceDirChange() { return m_bPrevFaceDir != GetFaceDir(); };

    // 플랫폼에 착지하면 점프 관련 수치들을 리셋해주는 함수
    void ResetJump() { m_bDoubleJump = true; }
    void OffDoubleJump() { m_bDoubleJump = false; }
    bool CanDoubleJump() const { return m_bDoubleJump; }

    bool CanGoDown() const { return m_bGoDown; }
    void SetGoDown(bool _bGoDown) { m_bGoDown = _bGoDown; }

    bool IsDuck() const { return m_bIsDuck; }

    EPLAYER_STATE GetPlayerState() const { return m_eState; }

    void SetWeapon(CWeapon* _pWeapon) { m_pWeapon = _pWeapon; }
    CWeapon* GetWeapon() const { return m_pWeapon; }

public:
    CLONE(CPlayer);

public:
    CPlayer();
    CPlayer(const CPlayer& _pOrigin);
    ~CPlayer();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)    override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

public:
    void Duck();
    void GetUp();

    bool Attack();

private:
    void LoadAnim(const wstring& _strFile);
};

