#pragma once
#include "CComponent.h"

class CObj;
class CState;

class CAI :
    public CComponent
{
private:
    map<wstring, CState*>   m_mapState;
    CState*                 m_pCurState;

public:
    CState* GetCurState() const { return m_pCurState; }

public:
    CLONE(CAI);

public:
    CAI(CObj* _pOwner);
    CAI(const CAI& _Other);
    ~CAI();

public:
    virtual void Tick() override {};
    virtual void Final_Tick()   override;
    virtual void Render(HDC _DC)   override {};

public:
    void AddState(const wstring& _strKey, CState* _pState);
    CState* FindState(const wstring& _strKey);

    void ChangeState(const wstring& _strKey);
};

