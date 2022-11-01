#pragma once
#include "CObj.h"

class CTexture;

class CItem :
    public CObj
{
private:
    CTexture* m_pItemTex;

public:
    void SetItemTex(CTexture* _pTex) { m_pItemTex = _pTex; }
    CTexture* GetItemTex() { return m_pItemTex; }

public:
    CLONE_DEACTIVATE(CItem);

public:
    CItem();
    ~CItem();

public:
    virtual void Render(HDC _DC) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;
};

