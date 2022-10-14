#pragma once
#include "CObj.h"

class CTexture;

class CUI :
    public CObj
{
private:
    vector<CUI*>    m_vecChildUI;
    CUI*            m_pParentUI;
    Vec2            m_vFinalPos;

    CTexture*       m_pIdleTex;

    bool            m_bLbtnDown;
    bool            m_bMouseOn;
    bool            m_bCmrAfctd;

public:
    void SetIdleTex(CTexture* _pTex);
    CTexture* GetIdleTex() const { return m_pIdleTex; }
    void SetFinalPos(Vec2 _vPos) { m_vFinalPos = _vPos; }
    Vec2 GetFinalPos() const { return m_vFinalPos; }
    void SetCameraAffected(bool _bSet) { m_bCmrAfctd = _bSet; }
    bool IsCameraAffected() const { return m_bCmrAfctd; }
    bool IsMouseOn() const { return m_bMouseOn; }
    bool IsLbtnDown() const { return m_bLbtnDown; }

    CUI* GetParentUI() const { return m_pParentUI; }
    const vector<CUI*>& GetChildUI()  { return m_vecChildUI; }

    void AddChildUI(CUI* _pChildUI)
    {
        _pChildUI->m_pParentUI = this;
        m_vecChildUI.push_back(_pChildUI);
    }



public:
    CLONE(CUI);

public:
    CUI();
    CUI(const CUI& _Other);
    ~CUI();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

    void Render_ChildUI(HDC _DC);

    // UI 이벤트 함수
public:
    // 오버라이딩 할 경우 부모함수 호출할 것
    virtual void MouseLbtnDown() { m_bLbtnDown = true; };
    virtual void MouseLbtnClicked() {};
    virtual void MouseOn() {};

private:
    void MouseOnCheck();

    friend class CUIMgr;
};

