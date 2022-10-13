#pragma once
#include "CUI.h"

class CEditorLevel;

typedef void(CEntity::* DELEGATE)(void);

class CButton :
    public CUI
{
private:
    CTexture* m_pPressTex;
    CTexture* m_pHighlightTex;

    // Delegate
    CEntity* m_pInst;
    DELEGATE m_pDelegateFunc;
    
public:
    void SetDelegate(CEntity* _pInst, DELEGATE _Func) { m_pInst = _pInst; m_pDelegateFunc = _Func; }

    void SetPressTex(CTexture* _pTex) { m_pPressTex = _pTex; }
    void SetHighlightTex(CTexture* _pTex) { m_pHighlightTex = _pTex; }

public:
    CLONE(CButton);

public:
    CButton();
    ~CButton();

public:
    virtual void Render(HDC _DC)    override;

public:
    virtual void MouseLbtnDown()    override;
    virtual void MouseLbtnClicked() override;
};

