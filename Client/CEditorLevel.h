#pragma once
#include "CLevel.h"

enum class EEDITOR_MODE
{
    TILE,
    ANIMATINON,
    OBJECT,


    NONE
};

class CEditorLevel :
    public CLevel
{
private:
    HMENU m_hMenu;

    EEDITOR_MODE m_eMode;

public:
    CEditorLevel();
    ~CEditorLevel();

public:
    CLONE_DEACTIVATE(CEditorLevel);

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Enter()    override;
    virtual void Exit() override;

private:
    void Update();
    void Tile_Update();

public:
    void SaveTile();
    void LoadTile();
};

