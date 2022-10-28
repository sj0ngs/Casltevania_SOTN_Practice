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
    PLAYER_START_POINT,
    SPAWN_POINT,
    OBJECT,
    TRIGGER,
    
    NONE
};

class CEditorLevel :
    public CLevel
{
private:
    HMENU m_hMenu;

    // ������ ��� ����
    EEDITOR_MODE m_eMode;   // ���� �������� ���

    // �ٴ� ����
    EFLOOR_OPTION m_eFloorOption;   // ���� �ٴ� �ɼ�

    // ������Ʈ ����
    EOBJ_OPTION m_eObjectOption;    // ���� ������Ʈ �ɼ�

    // ������Ʈ ����
    ESPAWNABLE_OBJECT m_eSpawnObjectOption;    // ���� ���� ����Ʈ �ɼ�
    bool m_bFaceDir; // �ٶ󺸴� ����    

    // Trigger ����
    ETRIGGER_TYPE   m_eTriggerType;
    ELEVEL_TYPE     m_eChangeLevelType;

    // Map Editor ù ��° ���콺 ��ǥ
    Vec2 m_vMousePos1;

public:
    void ChangeEditorMode(EEDITOR_MODE _eMode) { m_eMode = _eMode; }
    EEDITOR_MODE GetEditorMode() const { return m_eMode; }

    void ChangeFloorOption(EFLOOR_OPTION _eOption) { m_eFloorOption = _eOption; }
    EFLOOR_OPTION GetFloorOption() const { return m_eFloorOption; }

    void ChangeObjectOption(EOBJ_OPTION _eOption) { m_eObjectOption = _eOption; }
    EOBJ_OPTION GetObjOption()  const { return m_eObjectOption; }

    void ChangeSpawnObjectOption(ESPAWNABLE_OBJECT _eOption) { m_eSpawnObjectOption = _eOption; }
    ESPAWNABLE_OBJECT GetSpawnObjectOption() const { return m_eSpawnObjectOption; }

    void ChangeDir(bool bFaceDir) { m_bFaceDir = bFaceDir; }
    bool GetDir() const { return m_bFaceDir; }

    void ChangeTriggerType(ETRIGGER_TYPE _eType) { m_eTriggerType = _eType; }
    ETRIGGER_TYPE GetTriggerType() const { return m_eTriggerType; }

    void ChangeLevelType(ELEVEL_TYPE _eType) { m_eChangeLevelType = _eType; }
    ELEVEL_TYPE GetChangeLevelType() const { return m_eChangeLevelType; }

public:
    CEditorLevel();
    ~CEditorLevel();

public:
    CLONE_DEACTIVATE(CEditorLevel);

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
    virtual void Enter()    override;
    virtual void Exit() override;

private:
    void Update();
    void Map_Update();
    void Object_Update();

    void CreateUI(Vec2 _vResolution);

public:
    void SetBackGroundImg();
    void SetForeGroundImg();

private:
    // Map ��ġ
    void EditPlatform();
    void EditLine();

    // Object ��ġ
    void EditSpawnPoint();
    void EditObject();
    void EditTrigger();

public:
    // Map Save
    void SaveBackGround(FILE* _pFile);
    void SaveForeGround(FILE* _pFile);
    void SavePlatform(FILE* _pFile);
    void SaveLine(FILE* _pFile);

    // Object Save
    void SaveStartPoint(FILE* _pFile);
    void SaveSpawnPoint(FILE* _pFile);
    void SaveTrigger(FILE* _pFile);

    void SaveLevel();
    void LoadLevel();
};

