#pragma once
#include "CEntity.h"

class CObj;

class CLevel :
    public CEntity
{
private:
    std::vector<CObj*> m_arrLayer[(UINT)ELAYER::END];

    UINT                m_iTileXCount;
    UINT                m_iTileYCount;

public:
    UINT GetTileXCount()    const { return m_iTileXCount; }
    UINT GetTileYCount()    const { return m_iTileYCount; }

public:
    CLONE_DEACTIVATE(CLevel);

public:
    CLevel();
    virtual ~CLevel();

public:
    virtual void Init() = 0;    // 보유중인 모든 오브젝트를 생성및 초기화 시켜준다
    virtual void Tick();
    virtual void Final_Tick();
    virtual void Render(HDC _DC);

    virtual void Enter() = 0;   // 레벨에 진입할 때 호출
    virtual void Exit() = 0;    // 레벨에서 떠날 때 호출

public:
    void AddObj(CObj* _pObj, ELAYER _Layer) { m_arrLayer[(UINT)_Layer].push_back(_pObj); }
    const vector<CObj*>& GetLayer(ELAYER _Layer) { return m_arrLayer[(UINT)_Layer]; }
    void DeleteAllObject();
    void DeleteObject(ELAYER _Layer);

    void CreateTile(UINT _X, UINT _Y);

    void SetFocusedUI(CObj* _pUI);
};

