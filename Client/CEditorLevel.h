#pragma once
#include "CLevel.h"

enum class EEDITOR_MODE
{
    TILE,
    ANIMATINON,
    OBJECT,
    MAP,

    NONE
};

enum class EMAP_MODE
{
    SOLID_PLATFORM,
    NON_SOLID_PLATFORM,
    UP_LINE,
    DOWN_LINE
};

class CEditorLevel :
    public CLevel
{
private:
    HMENU m_hMenu;

    EEDITOR_MODE m_eMode;

    EMAP_MODE m_eMapMode;

    // Map Editor ¸¶¿ì½º ÁÂÇ¥
    Vec2 m_vMousePos1;

public:
    void ChangeMapMode(EMAP_MODE _eMode) { m_eMapMode = _eMode; }
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
    void Animation_Update();
    void Object_Update();
    void Map_Update();
    void CreateUI(Vec2 _vResolution);

private:
    void EditPlatform();
    void EditLine();

public:
    void SaveTile();
    void LoadTile();
    void LoadBackGround();

    void SaveLevel();
    void LoadLevel();
};

