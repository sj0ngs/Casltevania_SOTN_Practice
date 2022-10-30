#pragma once
#include "CObj.h"

class CTexture;
class CPlayer :
    public CObj
{
private:
    float m_fSpeed;

    bool m_bPrevFaceDir;     // 이전 프레임 바라보던 방향

    bool m_bDoubleJump;     // 더블 점프 가능 여부

    bool m_bGoDown;

public:
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
    float GetSpeed() const { return m_fSpeed; }

    bool IsFaceDirChange() { return m_bPrevFaceDir != GetFaceDir(); };

    // 플랫폼에 착지하면 점프 관련 수치들을 리셋해주는 함수
    void ResetJump() { m_bDoubleJump = true; }

    void OffDoubleJump() { m_bDoubleJump = false; }
    bool CanDoubleJump() const { return m_bDoubleJump; }

    bool CanGoDown() const { return m_bGoDown; }
    void SetGoDown(bool _bGoDown) { m_bGoDown = _bGoDown; }

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

private:
    void LoadAnim(const wstring& _strFile);
};

