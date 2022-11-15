#pragma once
#include "CLevel.h"

class CTexture;

class CEndingLevel :
    public CLevel
{
private:
    CTexture* m_pEnding;
    Vec2 m_vScenePos;

    bool m_bScrollEnd;

public:
    CLONE_DEACTIVATE(CEndingLevel);

public:
    CEndingLevel();
    ~CEndingLevel();

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render(HDC _DC);
    virtual void Enter()    override;
    virtual void Exit() override;
};

