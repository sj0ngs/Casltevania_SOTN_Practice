#pragma once
#include "CObj.h"

enum class ESUB_WEAPON_TYPE
{
    DAGGER,
    AXE,
    WATCH,
    HOLY_WATER,
    BIBLE,

    NONE
};

const float ATTACK_COOL = 0.7f;
const float DAGGER_COOL = 0.1f;
const float AXE_COOL = 1.f;

const int   USE_DAGGER = 1;
const int   USE_AXE = 5;
const int   USE_BIBLE = 5;

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
    bool m_bIsHit;

    EPLAYER_STATE m_eState;

    float m_fAttackAcc;
    CWeapon* m_pWeapon;

    ESUB_WEAPON_TYPE m_eSubWeapon;

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

    void SetWeapon(CWeapon* _pWeapon);
    CWeapon* GetWeapon() const { return m_pWeapon; }

    void ChangeSubWeapon(ESUB_WEAPON_TYPE _eType) { m_eSubWeapon = _eType; }

    bool IsHit() const { return m_bIsHit; }
    void EndHit() { m_bIsHit = false; }

public:
    CLONE(CPlayer);

public:
    CPlayer();
    CPlayer(const CPlayer& _pOrigin);
    ~CPlayer();
    void Copy(CPlayer* _Other);

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
    
    void Skill();

    void UseSubWeapon();
    void UseDagger();
    void UseAxe();
    void UseBible();

    void TakeDamage(int _iDmg, bool _bDir);
    int GetDamage();

private:
    void LoadAnim(const wstring& _strFile);
};

