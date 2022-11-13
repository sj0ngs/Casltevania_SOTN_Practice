#pragma once
#include "CObj.h"

class CTexture;

class CUI :
    public CObj
{
private:
    vector<CUI*>    m_vecChildUI;   // 자식 ui 
    CUI*            m_pParentUI;    // 부모 ui
    Vec2            m_vFinalPos;    // 최상위 부모 ui 부터 오프셋을 줘서 계산한 자신의 최종 위치

    CTexture*       m_pIdleTex;     // 일반 텍스쳐
 
    bool            m_bMouseAfctd;  // 마우스 입력을 받는지 여부
    bool            m_bLbtnDown;    // 좌버튼이 눌러졌는지 여부
    bool            m_bMouseOn;     // 마우스가 자신에 올라와 있는지 여부
    bool            m_bCmrAfctd;    // 카메라에 영향을 받는지 여부

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
        // 자신을 부모로 지정해준다
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

