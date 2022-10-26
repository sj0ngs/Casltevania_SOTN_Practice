#pragma once
#include "CLevel.h"

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

    // Animation 저장 모드
    CTexture* m_pAtlas;

    bool m_bReverse;

    CAnimation* m_pAnim;

    // Frame 수정 모드

public:
    CTexture* GetAtlasTex() const { return m_pAtlas; }

    void SwtichReverse() { m_bReverse = m_bReverse ? false : true; }
    void OffReverse() { m_bReverse = false; }
    bool GetReverse() const { return m_bReverse; }

public:
    CAnimationEditor();
    ~CAnimationEditor();

public:
    CLONE_DEACTIVATE(CAnimationEditor);

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Enter()    override;
    virtual void Exit() override;

private:
    // update
    void Update();

public:
    // Create 기능
    void SetAtlasTex();

    void CreateAnim(const wstring& _strName, CTexture* _pAtlas, Vec2 _vLeftTop, Vec2 _vBorder, 
        int iRow, int iCol, Vec2 _vSize, int _iMaxFrmCount, float _fDuration, Vec2 _vPadding, Vec2 _vOffset, bool _bReverse);
};

