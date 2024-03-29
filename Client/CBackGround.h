#pragma once
#include "CObj.h"

class CTexture;

class CBackGround :
    public CObj
{
private:
    CTexture* m_pBackGroundTex;

    bool m_bIsForeGround;

public:
    void SetBackGroundImg(CTexture* _pTex) { m_pBackGroundTex = _pTex; };
    void SetIsForeGround(bool _bSet) { m_bIsForeGround = _bSet; }

    const CTexture* GetTex() const { return m_pBackGroundTex; };

public:
    CLONE_DEACTIVATE(CBackGround);

public:
    CBackGround();
    ~CBackGround();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC) override;

public:
    virtual void Save(FILE* _pFile) override;
    virtual void Load(FILE* _pFile) override;
};

