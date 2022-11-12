#pragma once
#include "CTrigger.h"

class CTexture;

class CButtonTrigger :
    public CTrigger
{
private:
    UINT m_iBoxIdx;
    CTexture* m_pTex;

    Vec2 m_vOffset;

public:
    void SetBoxIdx(UINT _iIdx) { m_iBoxIdx = _iIdx; }
    UINT GetBoxIdx() const { return m_iBoxIdx; }

public:
    CLONE(CButtonTrigger);

public:
    CButtonTrigger();
    ~CButtonTrigger();

public:
    virtual void Render(HDC _DC) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

public:
    virtual void Save(FILE* _pFile) override;
    virtual void Load(FILE* _pFile) override;
};

