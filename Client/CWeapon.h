#pragma once
#include "CObj.h"

const wstring strPath = L"animation\\Weapon\\";

class CEffect;
class CPlayer;

class CWeapon :
    public CObj
{
private:
    tWeaponInfo m_tInfo;
    
    CPlayer* m_pOwner;

    // 만들어줄 이펙트 애니메이션 경로
    wstring m_strSwordRight;
    wstring m_strSwordLeft;

    wstring m_strJumpSwordRight;
    wstring m_strJumpSwordLeft;

    wstring m_strEffectRight;
    wstring m_strEffectLeft;

    wstring m_strJumpEffectRight;
    wstring m_strJumpEffectLeft;

    CEffect* m_pSword;
    CEffect* m_pEffect;

public:
    void SetOwner(CPlayer* _pPlayer) { m_pOwner = _pPlayer; }

    void SetWeaponInfo(const tWeaponInfo& _tInfo) { m_tInfo = _tInfo; };
    const tWeaponInfo& GetWeaponInfo() const { return m_tInfo; }

    void SetWeaponAnim(const wstring& _SR, const wstring& _SL, const wstring& _SJR, const wstring& _SJL,
                        const wstring& _ER, const wstring& _EL, const wstring& _EJR, const wstring& _EJL)
    {
        m_strSwordRight = _SR; 
        m_strSwordLeft = _SL; 
        m_strJumpSwordRight = _SJR;
        m_strJumpSwordLeft = _SJL;

        m_strEffectRight =_ER;
        m_strEffectLeft = _EL;
        m_strJumpEffectRight = _EJR;
        m_strJumpEffectLeft = _EJL;
    }

public:
    CLONE(CWeapon);

public:
    CWeapon();
    CWeapon(const CWeapon& _pOrigin);
    ~CWeapon();

public:
    virtual void Tick() override;

public:
    void Attack(bool _bDir);
    void AttackEnd();
};

