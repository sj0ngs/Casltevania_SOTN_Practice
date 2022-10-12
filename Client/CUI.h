#pragma once
#include "CObj.h"
class CUI :
    public CObj
{
private:
    bool m_bLbtnPressed;
    bool m_bMouseOn;

public:
    CLONE(CUI);

public:
    CUI();
    ~CUI();

public:
    virtual void Tick() override;
    virtual void Render()   override;

public:
    virtual void MouseLbtnDown() { m_bLbtnPressed = true; };
    virtual void MouseLbtnClicked() {};
    virtual void MouseOn() {};
};

