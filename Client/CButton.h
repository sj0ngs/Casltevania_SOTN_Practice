#pragma once
#include "CUI.h"

class CEditorLevel;

typedef void(CEntity::* DELEGATE)(void);

class CButton :
    public CUI
{
private:
    // Delegate
    CEntity* m_pInst;
    DELEGATE m_pDelegateFunc;

public:
    CLONE(CButton);

public:
    CButton();
    ~CButton();

public:
public:
    virtual void MouseLbtnClicked() override;
};

