#pragma once
#include "CUI.h"

class CEditorLevel;

typedef void(CEntity::* DELEGATE)(void);

class CButton :
    public CUI
{
private:
    CTexture* m_pIdleTex;
    CTexture* m_pDownTex;
    CTexture* m_pHighlightTex;

    // Delegate
    CEntity* m_pInst;
    DELEGATE m_pDelegateFunc;
    
public:
    void SetDelegate(CEntity* _pInst, DELEGATE _Func) { m_pInst = _pInst; m_pDelegateFunc = _Func; }

    void SetIdleTex(CTexture* _pTex) { m_pIdleTex = _pTex; }
    void SetDownTex(CTexture* _pTex) { m_pDownTex = _pTex; }
    void SetHighlightTex(CTexture* _pTex) { m_pHighlightTex = _pTex; }

public:
    CLONE(CButton);

public:
    CButton();
    ~CButton();

public:
    virtual void Render(HDC _DC)    override;

public:
    virtual void MouseLbtnClicked() override;
};

