#pragma once
#include "CObj.h"

class CTrigger :
    public CObj
{
private:
    ELEVEL_TYPE m_eLevelType;

public:
    CTrigger();
    ~CTrigger();

public:
    virtual void Render(HDC _DC) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

public:
    virtual void Save(FILE* _pFile) override;
    virtual void Load(FILE* _pFile) override;
};

