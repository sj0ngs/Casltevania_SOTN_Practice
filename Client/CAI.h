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
    CLONE(CAI);

public:
    CAI(CObj* _pOwner);
    ~CAI();

public:
    virtual void Tick() override;
    virtual void Final_Tick()   override;

public:
    void AddState(wstring& _strKey, CState* _pState) { m_mapState.insert(make_pair(_strKey, _pState)); }
    CState* FindState(const wstring& _strKey);
};

