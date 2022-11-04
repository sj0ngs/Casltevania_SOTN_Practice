#pragma once
#include "CEntity.h"

class CObj;
class CLine;
class CPlayer;

class CLevel :
    public CEntity
{
private:
    vector<CObj*>       m_arrLayer[(UINT)ELAYER::END];
    vector<CLine*>      m_vecLine;
    vector<CObj*>       m_vecTile;

    UINT                m_iStartPointIdx;
    UINT                m_iTileXCount;
    UINT                m_iTileYCount;

    UINT                m_iWidth;
    UINT                m_iHeight;

public:
    void SetStartPointIdx(UINT _iIdx) { m_iStartPointIdx = _iIdx; }
    UINT GetStartPointIdx() const { return m_iStartPointIdx; }

    UINT GetTileXCount()    const { return m_iTileXCount; }
    UINT GetTileYCount()    const { return m_iTileYCount; }

    UINT GetLevelWidth()    const { return m_iWidth; }
    UINT GetLevelHeight()   const { return m_iHeight; }

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

    virtual void Enter();   // 레벨에 진입할 때 호출
    virtual void Exit();    // 레벨에서 떠날 때 호출

public:
    // 파일로 만들어둔 레벨 불러올때 필요한 함수들
    void LoadLevel(const wstring& _strRelativePath);

    // Map Load Func
    void LoadBackGround(FILE* _pFile);
    void LoadForeGround(FILE* _pFile);
    void LoadPlatform(FILE* _pFile);
    void LoadLine(FILE* _pFile);

    // Object Load Fucn
    void LoadStartPoint(FILE* _pFile);
    void LoadSpawnPoint(FILE* _pFile);
    void LoadTrigger(FILE* _pFile);

public:
    void AddObj(CObj* _pObj, ELAYER _Layer);
    const vector<CObj*>& GetLayer(ELAYER _Layer) { return m_arrLayer[(UINT)_Layer]; }
    CPlayer* GetPlayer();

    void DeleteAllObject();
    void DeleteObject(ELAYER _Layer);

    void CreateTile(UINT _X, UINT _Y);

    void SetFocusedUI(CObj* _pUI);

private:
    void FindTileSreen();
};

