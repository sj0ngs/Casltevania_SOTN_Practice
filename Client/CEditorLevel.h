#pragma once
#include "CLevel.h"

enum class EEDITOR_MODE
{
    FLOOR,
    OBJECT,
    NONE
};

enum class EFLOOR_OPTION
{
    FLOOR,
    PLATFORM,
    UP_LINE,
    DOWN_LINE,
    
    NONE
};

enum class EOBJ_OPTION
{
    SPAWN_POINT,
    OBJECT,
    TRIGGER,
    
    NONE
};

enum class ESPAWN_POINT_OPTION
{
    PLAYER,
    BONE_SCIMITAR,
    AXE_ARMOR,
    SKELETON,
    SPITTLE_BONE,

    NONE
};

class CEditorLevel :
    public CLevel
{
private:
    HMENU m_hMenu;

    EEDITOR_MODE m_eMode;

    EFLOOR_OPTION m_eFloorOption;

    EOBJ_OPTION m_eObjectOption;

    ESPAWN_POINT_OPTION m_eSpawnPointOption;

    // Map Editor ¸¶¿ì½º ÁÂÇ¥
    Vec2 m_vMousePos1;

public:
    void ChangeEditorMode(EEDITOR_MODE _eMode) { m_eMode = _eMode; }
    void ChangeFloorOption(EFLOOR_OPTION _eOption) { m_eFloorOption = _eOption; }
    void ChangeObjectOption(EOBJ_OPTION _eOption) { m_eObjectOption = _eOption; }
    void ChangeSpawnPointOption(ESPAWN_POINT_OPTION _eOption) { m_eSpawnPointOption = _eOption; }

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
    void Map_Update();
    void Object_Update();

    void CreateUI(Vec2 _vResolution);

private:
    void EditPlatform();
    void EditLine();

public:
    void SaveTile();
    void LoadTile();
    void SetBackGroundImg();
    void SetForeGroundImg();

    void SaveBackGround(FILE* _pFile);
    
    void SaveForeGround(FILE* _pFile);

    void SavePlatform(FILE* _pFile);

    void SaveLine(FILE* _pFile);

    void SaveLevel();
    void LoadLevel();
};

