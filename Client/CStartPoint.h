#pragma once
#include "CObj.h"

class CTexture;

class CStartPoint :
    public CObj
{
private:
    UINT m_iIdx;
    CTexture* m_pTexture;

public:
    void SetStartIdx(UINT _iIdx) { m_iIdx = _iIdx; }

public:
    CLONE(CStartPoint);

public:
    CStartPoint();
    ~CStartPoint();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;

public:
    virtual void Save(FILE* _pFile) override;
    virtual void Load(FILE* _pFile) override;
};

