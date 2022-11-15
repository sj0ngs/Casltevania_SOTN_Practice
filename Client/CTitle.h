#pragma once
#include "CLevel.h"

#include "CTexture.h"

enum class ETITLE_SELECT
{
    START,
    DEBUG
};

class CTitle :
    public CLevel
{
private:
    CTexture* m_pBackGround;
    CTexture* m_pTitle;
    CTexture* m_pStartMode;
    CTexture* m_pDebugMode;
    CTexture* m_pSelect;

    ETITLE_SELECT m_eSelect;
    Vec2 m_vTitle;
    Vec2 m_vStartMode;
    Vec2 m_vDebugMode;

    float m_faccStartTime;
    bool  m_bStart;

public:
    CLONE_DEACTIVATE(CTitle);

public:
    CTitle();
    ~CTitle();

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render(HDC _DC);
    virtual void Enter()    override;
    virtual void Exit() override;
   
private:
    void ChangeMode();
};

