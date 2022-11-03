#pragma once
#include "CProjectile.h"

class CPlayerProjectile :
    public CProjectile
{
private:
    bool m_bPenetrate;  // 몬스터 관통 옵션

public:
    void SetPenatrate(bool _bPenetrate) { m_bPenetrate = _bPenetrate; }
    bool GetPenatrate() const { return m_bPenetrate; }

public:
    CLONE_DEACTIVATE(CPlayerProjectile);

public:
    CPlayerProjectile();
    ~CPlayerProjectile();

public:
    virtual void Render(HDC _DC) override {};

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;
};

