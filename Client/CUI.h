#pragma once
#include "CObj.h"
class CUI :
    public CObj
{
private:
    bool m_bLbtnDown;
    bool m_bMouseOn;

    bool m_bCmrAfctd;

public:
    void SetCameraAffected(bool _bSet) { m_bCmrAfctd = _bSet; }
    bool IsMouseOn() const { return m_bMouseOn; }
    bool IsLbtnDown() const { return m_bLbtnDown; }

public:
    CLONE(CUI);

public:
    CUI();
    ~CUI();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)   override;

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

