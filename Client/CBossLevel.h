#pragma once
#include "CLevel.h"

class CPlatform;
class CTexture;

class CBossLevel :
    public CLevel
{
private:
    CPlatform* m_pLeftBlock;
    CPlatform* m_pRightBlock;
    
    CTexture* m_pWallTex;

    Vec2 m_vLeftPos;
    Vec2 m_vRightPos;

    bool m_bBossEnd;

public:
    CLONE_DEACTIVATE(CBossLevel);

public:
    CBossLevel();
    ~CBossLevel();

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;
    virtual void Enter()    override;
    virtual void Exit() override;

private:
    void Block();
};

