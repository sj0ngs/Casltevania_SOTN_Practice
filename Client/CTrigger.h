#pragma once
#include "CObj.h"

class CTrigger :
    public CObj
{
private:
    ETRIGGER_TYPE m_eType;

public:
    void SetTriggerType(ETRIGGER_TYPE _eType) { m_eType = _eType; }
    ETRIGGER_TYPE GetTriggerType() const { return m_eType; }

public:
    CLONE_DEACTIVATE(CTrigger);

public:
    CTrigger();
    ~CTrigger();

public:
    virtual void Render(HDC _DC) override;

    virtual void BeginOverlap(CCollider* _pOther) override {};
    virtual void OnOverlap(CCollider* _pOther) override {};
    virtual void EndOverlap(CCollider* _pOther) override {};

public:
    virtual void Save(FILE* _pFile) override = 0;
    virtual void Load(FILE* _pFile) override = 0;
};

