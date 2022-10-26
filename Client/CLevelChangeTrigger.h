#pragma once
#include "CTrigger.h"

class CLevelChangeTrigger :
    public CTrigger
{
private:
    ELEVEL_TYPE m_eLevelChangeType;
    UINT m_iStartPointIdx;

public:
    void SetLevelType(ELEVEL_TYPE _eType) { m_eLevelChangeType = _eType; }
    ELEVEL_TYPE GetLevelType() const { return m_eLevelChangeType; }

    void SetStartPointIdx(UINT _iIdx) { m_iStartPointIdx = _iIdx; }
    UINT GetStartPointIdx() const { return m_iStartPointIdx; }

public:
    CLONE(CLevelChangeTrigger);

public:
    CLevelChangeTrigger();
    ~CLevelChangeTrigger();

public:
    virtual void Render(HDC _DC) override;

    virtual void BeginOverlap(CCollider* _pOther) override;
    virtual void OnOverlap(CCollider* _pOther) override;
    virtual void EndOverlap(CCollider* _pOther) override;

public:
    virtual void Save(FILE* _pFile) override;
    virtual void Load(FILE* _pFile) override;
};

