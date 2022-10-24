#pragma once
#include "CRes.h"

class CTexture :
    public CRes
{
private:
    HBITMAP m_hBit;
    HDC m_hDC;
    
    BITMAP m_tBitMapInfo;

public:
    UINT GetWidth() const { return m_tBitMapInfo.bmWidth; }
    UINT GetHeight() const { return m_tBitMapInfo.bmHeight; }

    HDC GetDC() { return m_hDC; }

    void Resize(UINT _iWidth, UINT _iHeight);

public:
    CTexture();
    ~CTexture();

private:
    virtual int Load(const wstring& _strFilePath) override;

public:
    void Create(UINT _iWidth, UINT _iHeight);
};

