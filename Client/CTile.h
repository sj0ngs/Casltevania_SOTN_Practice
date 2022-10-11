#pragma once
#include "CObj.h"

class CTexure;
class CTile :
    public CObj
{
private:
    CTexture*   m_pAtlas;
    int         m_iImgIdx;

public:
    void SetAtlas(CTexture* _pTex) { m_pAtlas = _pTex; }
    void SetImgIdx(int _iImgIdx);
    void AddImgIdx();

public:
    CLONE(CTile);

public:
    CTile();
    ~CTile();

public:
    virtual void Tick() override;
    virtual void Render(HDC _DC)    override;

public:
    void Save(FILE* _pFile);
    void Load(FILE* _pFile);
};

