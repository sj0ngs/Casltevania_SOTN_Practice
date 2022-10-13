#pragma once
#include "CUI.h"

class CPanel :
    public CUI
{
private:
    Vec2 m_vLeftRightPadding;
    Vec2 m_vTopBottomPadding;
    Vec2 m_vInnerPadding;

    Vec2 m_vPressPos;

public:
    CLONE(CPanel);

public:
    CPanel();
    ~CPanel();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;

public:
    virtual void MouseLbtnDown() override;
};

