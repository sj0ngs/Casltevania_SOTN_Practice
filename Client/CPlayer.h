#pragma once
#include "CObj.h"

enum class EPLAYER_STATE : UINT8
{
    IDLE1,
    WALK_START_LEFT,
    WALK_START_RIGHT,
    WALK_LEFT,
    WALK_RIGHT,
    JUMP,
    FALL,
    ATTACK,
    END
};

class CTexture;
class CPlayer :
    public CObj
{
private:
    float m_fSpeed;
    Vec2 m_vPrevPos;

    EPLAYER_STATE m_eState;
    EPLAYER_STATE m_ePrevState;
    int m_iFaceDir;

public:
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

    Vec2 GetPrevPos()   const    { return m_vPrevPos; }

    EPLAYER_STATE GetPlayerState()  const { return m_eState; }

public:
    CLONE(CPlayer);

public:
    CPlayer();
    CPlayer(const CPlayer& _Other);
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

