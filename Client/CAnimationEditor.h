#pragma once
#include "CLevel.h"

class CAnimDebug;

enum class EANIMATION_MODE
{
    ANIMATION,
    FRAME,

    END
};

class CTexture;
class CAnimation;

class CAnimationEditor :
    public CLevel
{
private:
    HMENU m_hMenu;

    EANIMATION_MODE m_eMode;
    CAnimDebug* m_pDebugObj;

    // Animation 저장 모드
    CTexture* m_pAtlas;
    bool m_bReverse;

    // Frame 수정 모드
    CAnimation* m_pAnim;
    vector<tAnimFrm>* m_pvecFrm;
    int m_iCurFrm;

    float m_fDuration;
    int   m_iOffsetX;
    int   m_iOffsetY;

public:
    void ChangeMode(EANIMATION_MODE _eMode) { m_eMode = _eMode; }

    CAnimDebug* GetDebugObj() const { return m_pDebugObj; }
    void ResetAnim() { m_pAnim = nullptr; }

    CTexture* GetAtlasTex() const { return m_pAtlas; }

    void SwtichReverse() { m_bReverse = m_bReverse ? false : true; }
    void OffReverse() { m_bReverse = false; }
    bool GetReverse() const { return m_bReverse; }

    void SetDuration(float _fDuration) { m_fDuration = _fDuration; }
    void SetOffsetX(int _iOffsetX) { m_iOffsetX = _iOffsetX; }
    void SetOffsetY(int _iOffsetY) { m_iOffsetY = _iOffsetY; }

public:
    CAnimationEditor();
    ~CAnimationEditor();

public:
    CLONE_DEACTIVATE(CAnimationEditor);

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
    virtual void Enter()    override;
    virtual void Exit() override;

private:
    // update
    void Update();
    void Frame_Update();

public:
    // Create 기능
    void SetAtlasTex();
    void CreateAnim(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vBorder, 
        int iRow, int iCol, Vec2 _vSize, int _iMaxFrmCount, float _fDuration, Vec2 _vPadding, Vec2 _vOffset, bool _bReverse);

    // Edit Frm 기능
    void LoadAnim();
    void EditFrame();
    void SaveAnim();
};

